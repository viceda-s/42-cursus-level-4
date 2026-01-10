/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:30:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/03 18:28:29 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_vector	get_sphere_normal(void *object_data, t_vector hit_point)
{
	t_sp		*sphere;
	t_vector	normal;

	sphere = (t_sp *)object_data;
	normal = vector_sub(hit_point, sphere->coord_colours.v);
	return (vector_normalize(normal));
}

t_vector	get_cylinder_normal(void *object_data, t_vector hit_point)
{
	t_cy		*cylinder;
	t_vector	axis;
	t_vector	center_to_hit;
	t_vector	projection;
	float		projection_length;

	cylinder = (t_cy *)object_data;
	axis = vector_normalize(cylinder->data.nov);
	center_to_hit = vector_sub(hit_point, cylinder->data.v);
	projection_length = vector_dot(center_to_hit, axis);
	projection = vector_scale(axis, projection_length);
	return (vector_normalize(vector_sub(center_to_hit, projection)));
}

t_vector	getting_normal_for_object(void *object_data,
	t_object_type type, t_vector hit_point)
{
	if (type == SPHERE)
		return (get_sphere_normal(object_data, hit_point));
	else if (type == PLANE)
		return (vector_normalize(((t_gd *)object_data)->nov));
	else if (type == CYLINDER)
		return (get_cylinder_normal(object_data, hit_point));
	else if (type == CUBE)
		return (get_cube_normal(object_data, hit_point));
	return ((t_vector){0, 1, 0});
}

t_gd	getting_material_color(void *object_data, t_object_type type)
{
	if (type == SPHERE)
		return (((t_sp *)object_data)->coord_colours);
	else if (type == PLANE)
		return (*((t_gd *)object_data));
	else if (type == CYLINDER)
		return (((t_cy *)object_data)->data);
	else if (type == CUBE)
		return (((t_cu *)object_data)->data);
	return ((t_gd){.r = 50, .g = 50, .b = 100,
		.v = {0, 0, 0}, .nov = {0, 0, 0}});
}
