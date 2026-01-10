/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lighting_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:30:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/06 14:01:19 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_gd	apply_ambient_light(t_gd material_color, t_al ambient)
{
	t_gd	color;

	color.r = (int)(material_color.r * ambient.ratio
			* ambient.colours.r / 255.0f);
	color.g = (int)(material_color.g * ambient.ratio
			* ambient.colours.g / 255.0f);
	color.b = (int)(material_color.b * ambient.ratio
			* ambient.colours.b / 255.0f);
	return (color);
}

t_gd	apply_diffuse_light(t_gd color, t_l *light_data, t_l *params,
		float shadow_factor)
{
	float	diff_intensity;

	diff_intensity = fmax(0.0f, vector_dot(params->normal, params->light_dir));
	diff_intensity *= shadow_factor;
	color.r += (int)(params->material_color.r * light_data->br * diff_intensity
			* light_data->coord.r / 255.0f);
	color.g += (int)(params->material_color.g * light_data->br * diff_intensity
			* light_data->coord.g / 255.0f);
	color.b += (int)(params->material_color.b * light_data->br * diff_intensity
			* light_data->coord.b / 255.0f);
	return (color);
}

t_gd	apply_specular_light(t_gd colour, t_l *light_data, t_l *l_params,
		float shadow_factor)
{
	t_vector	reflect_dir;
	float		spec_intensity;
	float		dot_multiplier;

	dot_multiplier = 2.0f * vector_dot(l_params->normal, l_params->light_dir);
	reflect_dir = vector_sub(vector_scale(l_params->normal, dot_multiplier),
			l_params->light_dir);
	spec_intensity = vector_dot(reflect_dir, l_params->view_dir);
	spec_intensity = powf(fmax(spec_intensity, 0.0f), SHININESS);
	spec_intensity *= shadow_factor;
	colour.r += (int)(light_data->coord.r * light_data->br * spec_intensity);
	colour.g += (int)(light_data->coord.g * light_data->br * spec_intensity);
	colour.b += (int)(light_data->coord.b * light_data->br * spec_intensity);
	return (colour);
}
