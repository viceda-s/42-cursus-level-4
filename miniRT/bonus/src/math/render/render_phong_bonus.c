/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_phong_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaldin <rbaldin@student.42luxembourg.lu>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 09:05:32 by rbaldin           #+#    #+#             */
/*   Updated: 2025/10/31 08:25:50 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * @brief Determines if a point is in shadow from the light source.
 * 
 * Casts a shadow ray from the hit point toward the light source and checks
 * if any object blocks the light. Uses a small offset along the normal to
 * avoid self-intersection.
 * 
 * @param hit_point The point being tested for shadow.
 * @param normal The surface normal at the hit point.
 * @param scene The scene containing all objects and the light source.
 * @return True if the point is in shadow, false otherwise.
 */
static bool	is_in_shadow(t_vector hit_point, t_vector normal, t_scene *scene)
{
	t_ray			shadow_ray;
	float			t;
	void			*shadow_hit_obj;
	t_object_type	shadow_hit_type;
	float			light_distance;

	shadow_ray.origin = vector_add(hit_point, vector_scale(normal, 1e-4f));
	shadow_ray.direction = vector_sub(scene->light.coord.v, shadow_ray.origin);
	light_distance = vector_length(shadow_ray.direction);
	shadow_ray.direction = vector_normalize(shadow_ray.direction);
	t = find_closest_intersection(shadow_ray, scene, &shadow_hit_obj,
			&shadow_hit_type);
	if (t > 0 && t < light_distance)
		return (true);
	return (false);
}

/**
 * @brief Applies ambient lighting to a material color.
 * 
 * Multiplies the material's RGB values by the ambient light ratio to
 * produce the ambient component of the final color.
 * 
 * @param material_color The base color of the material.
 * @param ambient The ambient light parameters.
 * @return The color after applying ambient lighting.
 */
static t_gd	apply_ambient_light(t_gd material_color, t_al ambient)
{
	t_gd	color;

	color.r = (int)(material_color.r * ambient.ratio);
	color.g = (int)(material_color.g * ambient.ratio);
	color.b = (int)(material_color.b * ambient.ratio);
	return (color);
}

/**
 * @brief Applies diffuse lighting to a color.
 * 
 * Calculates the diffuse reflection based on the angle between the surface
 * normal and the light direction (Lambertian reflection). Adds the diffuse
 * component to the existing color.
 * 
 * @param color The current color (typically after ambient lighting).
 * @param params Structure containing material color, scene, 
 *               normal, and light direction.
 * @return The color after applying diffuse lighting.
 */
static t_gd	apply_diffuse_light(t_gd color, t_l *params)
{
	float	diff_intensity;

	diff_intensity = fmax(0.0f, vector_dot(params->normal, params->light_dir));
	color.r += (int)(params->material_color.r
			* params->scene->light.br * diff_intensity);
	color.g += (int)(params->material_color.g
			* params->scene->light.br * diff_intensity);
	color.b += (int)(params->material_color.b
			* params->scene->light.br * diff_intensity);
	return (color);
}

/**
 * @brief Apply the Phong specular component to a colour.
 *
 * Computes the reflection direction of the incoming light about the surface
 * normal, evaluates the specular intensity as:
 *   spec = max(dot(reflect_dir, view_dir), 0) ^ SHININESS
 * and adds the light's contribution (scaled by the scene light brightness)
 * to each RGB channel of the input colour.
 *
 * @param colour The current accumulated colour (channels in 0..255).
 * @param l_params Pointer to lighting parameters:
 *        - l_params->normal : surface normal at the hit point
 *        - l_params->light_dir : normalized direction from surface to light
 *        - l_params->view_dir : normalized direction from surface
 *        to camera/view
 *        - l_params->scene : scene containing light brightness (light.br)
 * @return t_gd The colour with the specular component added
 *         (clamping done by caller).
 */
static t_gd	apply_specular_light(t_gd colour, t_l *l_params)
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

/**
 * @brief Calculates the final lighting for a surface point.
 * 
 * Combines ambient and diffuse lighting components. Checks for shadows and
 * only applies diffuse lighting if the point is not in shadow. Clamps the
 * final RGB values to the valid range [0, 255].
 * 
 * @param hit_point The point on the surface being lit.
 * @param normal The surface normal at the hit point.
 * @param scene The scene containing lighting and object information.
 * @param material_color The base color of the material.
 * @return The final computed color including all lighting effects.
 */
t_gd	calculate_lighting(t_shade *s)
{
	t_gd		final_color;
	t_l			params;
	t_gd		mat_color;

	mat_color = s->material_color;
	if (mat_color.checker == 1)
		mat_color = apply_checkerboard(s->hit_point, s->material_color,
				0.15f, s->hit_object, s->hit_type);
	final_color = apply_ambient_light(mat_color, s->scene->ambient);
	params.material_color = mat_color;
	params.scene = s->scene;
	params.normal = s->normal;
	params.light_dir = vector_normalize(vector_sub(s->scene->light.coord.v,
				s->hit_point));
	params.view_dir = vector_normalize(vector_scale(s->view_dir, -1));
	if (!is_in_shadow(s->hit_point, s->normal, s->scene))
	{
		final_color = apply_diffuse_light(final_color, &params);
		final_color = apply_specular_light(final_color, &params);
	}
	final_color.r = fmin(255, fmax(0, final_color.r));
	final_color.g = fmin(255, fmax(0, final_color.g));
	final_color.b = fmin(255, fmax(0, final_color.b));
	return (final_color);
}
