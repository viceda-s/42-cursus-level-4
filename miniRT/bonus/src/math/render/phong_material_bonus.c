/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_material_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:30:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/06 14:01:19 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_texture	*get_object_texture(t_shade *s)
{
	if (s->hit_type == SPHERE)
		return (((t_sp *)s->hit_object)->texture);
	else if (s->hit_type == PLANE)
		return (((t_gd *)s->hit_object)->texture);
	else if (s->hit_type == CYLINDER)
		return (((t_cy *)s->hit_object)->texture);
	else if (s->hit_type == CUBE)
		return (((t_cu *)s->hit_object)->texture);
	return (NULL);
}

static void	get_texture_uv(t_shade *s, float *u, float *v)
{
	if (s->hit_type == PLANE)
		map_plane_uv(s->hit_point, (t_gd *)s->hit_object, u, v);
	else if (s->hit_type == SPHERE)
		map_sphere_uv(s->hit_point, (t_sp *)s->hit_object, u, v);
	else if (s->hit_type == CYLINDER)
		map_cylinder_uv(s->hit_point, (t_cy *)s->hit_object, u, v);
	else if (s->hit_type == CUBE)
		map_cube_uv(s->hit_point, (t_cu *)s->hit_object, u, v);
}

t_gd	get_material_color_textured(t_shade *s)
{
	t_texture	*tex;
	float		u;
	float		v;

	tex = get_object_texture(s);
	if (tex)
	{
		u = 0.0f;
		v = 0.0f;
		get_texture_uv(s, &u, &v);
		return (get_texture_color(tex, u, v));
	}
	if (s->material_color.checker == 1)
		return (apply_checkerboard(s, 0.15f));
	return (s->material_color);
}
