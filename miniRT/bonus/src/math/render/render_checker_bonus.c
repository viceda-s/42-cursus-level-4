/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_checker_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:22:19 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/05 20:07:23 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
 * cube_checker_color - get checker color for cube based on brightness
 * @c: input colour (t_gd) with .r, .g, .b in 0..255 and .checker flag
 *
 * Return: new t_gd with fixed colors based on brightness and
 * .checker set to false.
 */
static t_gd	cube_checker_color(t_gd c)
{
	int	brightness;

	brightness = (c.r + c.g + c.b) / 3;
	if (brightness > 127)
	{
		c.r = 30;
		c.g = 30;
		c.b = 30;
	}
	else
	{
		c.r = 245;
		c.g = 245;
		c.b = 245;
	}
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

/*
** Object-aware checkerboard. Returns base colour or inverted colour.
*/

t_gd	apply_checkerboard(t_shade *s, float scale)
{
	t_gd	res;
	float	u;
	float	v;
	t_shade	*sh;

	sh = s;
	if (!sh)
		return ((t_gd){0, 0, 0, false, false, 0.0f, \
{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, NULL, NULL});
	res = sh->material_color;
	if (!res.checker)
		return (res);
	u = 0.0f;
	v = 0.0f;
	if (sh->hit_type == PLANE)
		map_plane_uv(sh->hit_point, (t_gd *)sh->hit_object, &u, &v);
	else if (sh->hit_type == SPHERE)
		map_sphere_uv(sh->hit_point, (t_sp *)sh->hit_object, &u, &v);
	else if (sh->hit_type == CYLINDER)
		map_cylinder_uv(sh->hit_point, (t_cy *)sh->hit_object, &u, &v);
	else if (sh->hit_type == CUBE)
		map_cube_uv(sh->hit_point, (t_cu *)sh->hit_object, &u, &v);
	if (!parity_uv(u, v, scale))
	{
		res.checker = false;
		return (res);
	}
	if (sh->hit_type == CUBE)
		return (cube_checker_color(res));
	return (invert_color(res));
}
