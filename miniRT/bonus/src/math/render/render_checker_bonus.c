/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_checker_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg.>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:22:19 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/30 15:22:19 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "minirt_bonus.h"

/**
 * invert_color - invert RGB channels and clear checker flag
 * @c: input colour (t_gd) with .r, .g, .b in 0..255 and .checker flag
 *
 * Return: new t_gd with RGB channels inverted (255 - value) and
 * .checker set to false.
 */
static t_gd	invert_color(t_gd c)
{
	c.r = 255 - c.r;
	c.g = 255 - c.g;
	c.b = 255 - c.b;
	c.checker = false;
	return (c);
}

/**
 * parity_uv - compute checker parity from 2D coordinates and scale
 * @u: horizontal coordinate (float)
 * @v: vertical coordinate (float)
 * @scale: square size; if zero the function returns 0
 *
 * Uses floorf(u / scale) and floorf(v / scale) to obtain integer cell
 * indices. Sums the indices and returns 1 when odd, 0 when even.
 * Negative coordinates are handled correctly via floorf.
 *
 * Return: 1 if cell parity is odd, 0 otherwise
 */
static int	parity_uv(float u, float v, float scale)
{
	int	iu;
	int	iv;

	if (scale == 0.0f)
		return (0);
	iu = (int)floor(u / scale);
	iv = (int)floorf(v / scale);
	return (((iu + iv) & 1) != 0);
}

/**
 * map_plane_uv - compute local UV coordinates on a plane surface
 * @p: hit point in world space (t_vector)
 * @pl: pointer to plane data stored in t_gd (expects .nov normal and .v origin)
 * @u: pointer to output horizontal coordinate (float *)
 * @v: pointer to output vertical coordinate (float *)
 *
 * Constructs an orthonormal tangent/bitangent basis from the plane normal
 * and projects the vector from plane origin to the hit point onto that basis.
 * Outputs the resulting coordinates in *u and *v.
 */
static void	map_plane_uv(t_vector p, t_gd *pl, float *u, float *v)
{
	t_vector	n;
	t_vector	tan;
	t_vector	bit;
	t_vector	rel;

	n = pl->nov;
	rel = vector_sub(p, pl->v);
	if (fabsf(n.x) < 0.9f)
		tan = vector_normalize(vector_cross((t_vector){1, 0, 0}, n));
	else
		tan = vector_normalize(vector_cross((t_vector){0, 1, 0}, n));
	bit = vector_normalize(vector_cross(n, tan));
	*u = vector_dot(rel, tan);
	*v = vector_dot(rel, bit);
}

/**
 * map_sphere_uv - compute spherical UV coordinates for a sphere surface
 * @p: hit point in world space (t_vector)
 * @sp: pointer to sphere struct (t_sp), expects center in sp->coord_colours.v
 * @u: pointer to output horizontal coordinate in [0,1) (float *)
 * @v: pointer to output vertical coordinate in [0,1] (float *)
 * @pi: value of PI (float) passed by caller
 *
 * Converts the normalized direction from sphere center to hit point into
 * spherical angles theta and phi, then maps them to [0,1] ranges:
 * u = (theta + PI) / (2*PI), v = phi / PI.
 * If the point coincides with the center, returns u = v = 0.
 */
static void	map_sphere_uv(t_vector p, t_sp *sp, float *u, float *v,
				float pi)
{
	t_vector	d;
	float		r;
	float		nx;
	float		ny;
	float		nz;
	float		theta;
	float		phi;

	d = vector_sub(p, sp->coord_colours.v);
	r = vector_length(d);
	if (r == 0.0f)
	{
		*u = 0.0f;
		*v = 0.0f;
		return ;
	}
	nx = d.x / r;
	ny = d.y / r;
	nz = d.z / r;
	theta = atan2f(nz, nx);
	phi = acosf(fmaxf(-1.0f, fminf(1.0f, ny)));
	*u = (theta + pi) / (2.0f * pi);
	*v = phi / pi;
}

/**
 * map_cylinder_uv - compute angular and height coordinates for a cylinder
 * @p: hit point in world space (t_vector)
 * @cy: pointer to cylinder struct (t_cy), expects axis in cy->data.nov and
 *      origin in cy->data.v
 * @u: pointer to output angular coordinate in [0,1) (float *)
 * @v: pointer to output height coordinate (float *)
 * @pi: value of PI (float) passed by caller
 *
 * Computes the angle around the cylinder axis and maps it to u in [0,1).
 * Computes the projection of the hit point on the axis to obtain height.
 * If cy->h is non-zero the height is normalized to [0,1] using cy->h,
 * otherwise the raw height projection is returned in *v.
 */
static void	map_cylinder_uv(t_vector p, t_cy *cy, float *u, float *v,
				float pi)
{
	t_vector	axis;
	t_vector	rel;
	float		height;
	t_vector	tan;
	float		theta;

	axis = cy->data.nov;
	rel = vector_sub(p, cy->data.v);
	height = vector_dot(rel, axis);
	if (fabsf(axis.x) < 0.9f)
		tan = vector_normalize(vector_cross((t_vector){1, 0, 0}, axis));
	else
		tan = vector_normalize(vector_cross((t_vector){0, 1, 0}, axis));
	theta = atan2f(vector_dot(rel, vector_cross(axis, tan)),
			vector_dot(rel, tan));
	*u = (theta + pi) / (2.0f * pi);
	/* normalize height to [0,1] based on cylinder height */
	if (cy->h != 0.0f)
		*v = (height / cy->h) + 0.5f;
	else
		*v = height;
}

/*
** Object-aware checkerboard. Returns base colour or inverted colour.
*/

t_gd	apply_checkerboard(t_vector p, t_gd c1, float scale,
				void *object, t_object_type type)
{
	t_gd	res;
	float	u;
	float	v;

	if (!c1.checker)
		return (c1);
	u = 0.0f;
	v = 0.0f;
	if (type == PLANE)
		map_plane_uv(p, (t_gd *)object, &u, &v);
	else if (type == SPHERE)
		map_sphere_uv(p, (t_sp *)object, &u, &v, M_PI);
	else if (type == CYLINDER)
		map_cylinder_uv(p, (t_cy *)object, &u, &v, M_PI);
	/* even parity -> base, odd -> inverted */
	if (!parity_uv(u, v, scale))
	{
		res = c1;
		res.checker = false;
		return (res);
	}
	return (invert_color(c1));
}
