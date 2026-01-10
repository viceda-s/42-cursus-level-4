/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:59:42 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/06 11:03:08 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static float	get_object_bump_strength(void *obj, t_object_type type)
{
	if (type == SPHERE)
		return (((t_sp *)obj)->coord_colours.bump_strength);
	else if (type == PLANE)
		return (((t_gd *)obj)->bump_strength);
	else if (type == CYLINDER)
		return (((t_cy *)obj)->data.bump_strength);
	else if (type == CUBE)
		return (((t_cu *)obj)->data.bump_strength);
	return (1.0f);
}

static void	apply_bump_if_any(t_shade *s)
{
	float	strength_scale;
	float	freq_scale;
	float	user_strength;

	s->bump_intensity = 0.0f;
	user_strength = get_object_bump_strength(s->hit_object, s->hit_type);
	strength_scale = user_strength / (1.0f + s->distance * 0.015f);
	freq_scale = fmaxf(0.1f, 1.0f / (1.0f + s->distance * 0.025f));
	if (s->hit_type == SPHERE)
		apply_bump_sphere(s, strength_scale, freq_scale);
	else if (s->hit_type == PLANE)
		apply_bump_plane(s, strength_scale, freq_scale);
	else if (s->hit_type == CYLINDER)
		apply_bump_cylinder(s, strength_scale, freq_scale);
	else if (s->hit_type == CUBE)
		apply_bump_cube(s, strength_scale, freq_scale);
}

t_gd	trace_ray(t_ray ray, t_scene *scene)
{
	float			t;
	void			*hit_object;
	t_object_type	hit_type;
	t_shade			s;

	t = find_closest_intersection(ray, scene, &hit_object, &hit_type);
	if (t > 0)
	{
		s.hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
		s.normal = getting_normal_for_object(hit_object, hit_type, \
s.hit_point);
		s.view_dir = ray.direction;
		s.material_color = getting_material_color(hit_object, hit_type);
		s.scene = scene;
		s.hit_object = hit_object;
		s.hit_type = hit_type;
		s.distance = t;
		apply_bump_if_any(&s);
		return (calculate_lighting(&s));
	}
	return ((t_gd){.r = 0, .g = 0, .b = 0, .v = {0, 0, 0}, .nov = {0, 0, 0}});
}

int	color_to_int(t_gd color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}
