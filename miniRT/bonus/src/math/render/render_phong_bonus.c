/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_phong_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 09:05:32 by rbaldin           #+#    #+#             */
/*   Updated: 2025/11/05 18:30:14 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * @brief Determines if a point is in shadow from the light source.
 * 
 * Casts a shadow ray from the hit point toward the light source and checks
 * if any object blocks the light. Uses a small offset along the normal to
 * avoid self-intersection. For bump-mapped surfaces, applies soft shadowing.
 * 
 * @param hit_point The point being tested for shadow.
 * @param normal The surface normal at the hit point.
 * @param scene The scene containing all objects and the light source.
 * @param bump_intensity Intensity of bump mapping (0.0 = no bump, 1.0 = max).
 * @return Shadow factor (0.0 = full shadow, 1.0 = no shadow).
 */
static float	compute_shadow_factor(t_vector hit_point, t_vector normal,
		t_scene *scene, t_l *current_light)
{
	t_ray			shadow_ray;
	float			t;
	void			*shadow_hit_obj;
	t_object_type	shadow_hit_type;
	float			light_distance;
	float			epsilon;

	epsilon = 0.01f;
	shadow_ray.origin = vector_add(hit_point, vector_scale(normal, epsilon));
	shadow_ray.direction = vector_sub(current_light->coord.v,
			shadow_ray.origin);
	light_distance = vector_length(shadow_ray.direction);
	shadow_ray.direction = vector_normalize(shadow_ray.direction);
	t = find_closest_intersection(shadow_ray, scene, &shadow_hit_obj,
			&shadow_hit_type);
	if (t > 0 && t < light_distance)
		return (0.3f);
	return (1.0f);
}

/**
 * @brief Applies ambient lighting to a material color.
 * 
 * Multiplies the material's RGB values by the ambient light ratio AND
 * the ambient color to produce the ambient component of the final color.
 * Formula: ambient_ratio * (ambient_color / 255) * material_color
 *
 * @param material_color The base color of the material.
 * @param ambient The ambient light parameters.
 * @return The color after applying ambient lighting.
 */
static t_gd	apply_ambient_light(t_gd material_color, t_al ambient)
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

/**
 * @brief Applies diffuse lighting to a color with shadow factor.
 *
 * Calculates the diffuse reflection based on the angle between the surface
 * normal and the light direction (Lambertian reflection). Multiplies by
 * shadow_factor to create soft shadows. Adds the diffuse component to
 * the existing color.
 *
 * @param color The current color (typically after ambient lighting).
 * @param params Structure containing material color, scene,
 *               normal, and light direction.
 * @param shadow_factor Light occlusion (0.0 = full shadow, 1.0 = no shadow).
 * @return The color after applying diffuse lighting.
 */
static t_gd	apply_diffuse_light(t_gd color, t_l *light_data, t_l *params,
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
static t_gd	apply_specular_light(t_gd colour, t_l *light_data, t_l *l_params,
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

/**
 * @brief Get textured material color if available, otherwise return solid color.
 * 
 * Checks if the object has a texture. If yes, calculates UV coordinates
 * and samples the texture. If no, returns the solid material color.
 * Also applies checkerboard if enabled.
 * 
 * @param s Shade parameters with hit object and material color.
 * @return The final material color (textured or solid).
 */
static t_gd	get_material_color_textured(t_shade *s)
{
	t_texture	*tex;
	float		u;
	float		v;

	tex = NULL;
	u = 0.0f;
	v = 0.0f;
	if (s->hit_type == SPHERE)
		tex = ((t_sp *)s->hit_object)->texture;
	else if (s->hit_type == PLANE)
		tex = ((t_gd *)s->hit_object)->texture;
	else if (s->hit_type == CYLINDER)
		tex = ((t_cy *)s->hit_object)->texture;
	else if (s->hit_type == CUBE)
		tex = ((t_cu *)s->hit_object)->texture;
	if (tex)
	{
		if (s->hit_type == PLANE)
			map_plane_uv(s->hit_point, (t_gd *)s->hit_object, &u, &v);
		else if (s->hit_type == SPHERE)
			map_sphere_uv(s->hit_point, (t_sp *)s->hit_object, &u, &v);
		else if (s->hit_type == CYLINDER)
			map_cylinder_uv(s->hit_point, (t_cy *)s->hit_object, &u, &v);
		else if (s->hit_type == CUBE)
			map_cube_uv(s->hit_point, (t_cu *)s->hit_object, &u, &v);
		return (get_texture_color(tex, u, v));
	}
	if (s->material_color.checker == 1)
		return (apply_checkerboard(s, 0.15f));
	return (s->material_color);
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
	t_gd		mat_color;
	float		shadow_factor;
	t_list		*lights_node;
	t_l			current_light_params;
	t_l			*light_data;

	mat_color = get_material_color_textured(s);
	final_color = apply_ambient_light(mat_color, s->scene->ambient);
	lights_node = s->scene->lights_list;
	while (lights_node)
	{
		light_data = (t_l *)lights_node->content;
		current_light_params.material_color = mat_color;
		current_light_params.scene = s->scene;
		current_light_params.normal = s->normal;
		current_light_params.light_dir = \
vector_normalize(vector_sub(light_data->coord.v, s->hit_point));
		current_light_params.view_dir = \
vector_normalize(vector_scale(s->view_dir, -1));
		shadow_factor = compute_shadow_factor(s->hit_point, s->normal, s->scene,
				light_data);
		final_color = apply_diffuse_light(final_color, light_data,
				&current_light_params, shadow_factor);
		final_color = apply_specular_light(final_color, light_data,
				&current_light_params, shadow_factor);
		lights_node = lights_node->next;
	}
	final_color.r = fmin(255, fmax(0, final_color.r));
	final_color.g = fmin(255, fmax(0, final_color.g));
	final_color.b = fmin(255, fmax(0, final_color.b));
	return (final_color);
}
