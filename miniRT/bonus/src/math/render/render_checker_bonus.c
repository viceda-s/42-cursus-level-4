/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_checker_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:22:19 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/06 13:30:15 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_gd	invert_color(t_gd c)
{
	c.r = 255 - c.r;
	c.g = 255 - c.g;
	c.b = 255 - c.b;
	c.checker = false;
	return (c);
}

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

static void	get_object_uv(t_shade *sh, float *u, float *v)
{
	if (sh->hit_type == PLANE)
		map_plane_uv(sh->hit_point, (t_gd *)sh->hit_object, u, v);
	else if (sh->hit_type == SPHERE)
		map_sphere_uv(sh->hit_point, (t_sp *)sh->hit_object, u, v);
	else if (sh->hit_type == CYLINDER)
		map_cylinder_uv(sh->hit_point, (t_cy *)sh->hit_object, u, v);
	else if (sh->hit_type == CUBE)
		map_cube_uv(sh->hit_point, (t_cu *)sh->hit_object, u, v);
}

t_gd	apply_checkerboard(t_shade *s, float scale)
{
	t_gd	res;
	float	u;
	float	v;

	if (!s)
		return ((t_gd){0, 0, 0, false, false, 0.0f, \
{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, NULL, NULL});
	res = s->material_color;
	if (!res.checker)
		return (res);
	u = 0.0f;
	v = 0.0f;
	get_object_uv(s, &u, &v);
	if (!parity_uv(u, v, scale))
	{
		res.checker = false;
		return (res);
	}
	return (invert_color(res));
}
