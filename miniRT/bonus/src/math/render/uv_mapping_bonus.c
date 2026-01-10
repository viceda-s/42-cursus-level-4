/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 00:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/06 11:42:09 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	map_plane_uv(t_vector p, t_gd *pl, float *u, float *v)
{
	t_vector	n;
	t_vector	tan;
	t_vector	bit;
	t_vector	rel;
	float		scale;

	n = pl->nov;
	rel = vector_sub(p, pl->v);
	if (fabsf(n.x) < 0.9f)
		tan = vector_normalize(vector_cross((t_vector){1, 0, 0}, n));
	else
		tan = vector_normalize(vector_cross((t_vector){0, 1, 0}, n));
	bit = vector_normalize(vector_cross(n, tan));
	scale = 0.1f;
	*u = vector_dot(rel, tan) * scale;
	*v = vector_dot(rel, bit) * scale;
}

void	map_sphere_uv(t_vector p, t_sp *sp, float *u, float *v)
{
	t_vector	d;
	float		r;
	t_vector	n;
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
	n = vector_normalize(d);
	theta = atan2f(n.z, n.x);
	phi = acosf(fmaxf(-1.0f, fminf(1.0f, n.y)));
	*u = (theta + M_PI) / (2.0f * M_PI);
	*v = phi / M_PI;
}

void	map_cylinder_uv(t_vector p, t_cy *cy, float *u, float *v)
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
	*u = (theta + M_PI) / (2.0f * M_PI);
	if (cy->h != 0.0f)
		*v = (height / cy->h) + 0.5f;
	else
		*v = height;
}
