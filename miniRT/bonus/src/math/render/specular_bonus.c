//
// Created by rbaldin on 10/28/25.
//

#include "minirt_bonus.h"

t_gd	apply_specular_light(t_gd colour, t_l *l_params)
{
	t_vector	reflect_dir;
	float		spec_intensity;
	float		dot_multiplier;

	dot_multiplier = 2.0f * vector_dot(l_params->normal, l_params->light_dir);
	reflect_dir = vector_sub(vector_scale(l_params->normal, dot_multiplier), \
l_params->light_dir);
	spec_intensity = vector_dot(reflect_dir, l_params->view_dir);
	spec_intensity = powf(fmax(spec_intensity, 0.0f), SHININESS);
	colour.r += (int)(255 * l_params->scene->light.br * spec_intensity);
	colour.g += (int)(255 * l_params->scene->light.br * spec_intensity);
	colour.b += (int)(255 * l_params->scene->light.br * spec_intensity);
	return (colour);
}
