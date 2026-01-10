/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_phong_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 09:05:32 by rbaldin           #+#    #+#             */
/*   Updated: 2025/11/06 13:50:31 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

float	compute_shadow_factor(t_vector hit_point, t_vector normal,
		t_scene *scene, t_l *current_light)
{
	t_ray			shadow_ray;
	float			t;
	void			*shadow_hit_obj;
	t_object_type	shadow_hit_type;

	shadow_ray.origin = vector_add(hit_point, vector_scale(normal, 0.01f));
	shadow_ray.direction = vector_normalize(vector_sub(current_light->coord.v,
				shadow_ray.origin));
	t = find_closest_intersection(shadow_ray, scene, &shadow_hit_obj,
			&shadow_hit_type);
	if (t > 0 && t < vector_length(vector_sub(current_light->coord.v,
				shadow_ray.origin)))
		return (0.3f);
	return (1.0f);
}

static void	init_light_params(t_l *params, t_shade *s, t_gd mat, t_l *light)
{
	params->material_color = mat;
	params->scene = s->scene;
	params->normal = s->normal;
	params->light_dir = vector_normalize(vector_sub(light->coord.v,
				s->hit_point));
	params->view_dir = vector_normalize(vector_scale(s->view_dir, -1));
}

static t_gd	clamp_color(t_gd color)
{
	color.r = fmin(255, fmax(0, color.r));
	color.g = fmin(255, fmax(0, color.g));
	color.b = fmin(255, fmax(0, color.b));
	return (color);
}

t_gd	calculate_lighting(t_shade *s)
{
	t_gd	final_color;
	t_gd	mat_color;
	t_list	*lights_node;
	t_l		light_params;
	t_l		*light_data;

	mat_color = get_material_color_textured(s);
	final_color = apply_ambient_light(mat_color, s->scene->ambient);
	lights_node = s->scene->lights_list;
	while (lights_node)
	{
		light_data = (t_l *)lights_node->content;
		init_light_params(&light_params, s, mat_color, light_data);
		final_color = apply_diffuse_light(final_color, light_data,
				&light_params, compute_shadow_factor(s->hit_point, s->normal,
					s->scene, light_data));
		final_color = apply_specular_light(final_color, light_data,
				&light_params, compute_shadow_factor(s->hit_point, s->normal,
					s->scene, light_data));
		lights_node = lights_node->next;
	}
	return (clamp_color(final_color));
}
