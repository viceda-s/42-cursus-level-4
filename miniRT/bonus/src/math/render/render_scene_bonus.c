/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:11:31 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/27 19:10:35 by viceda-s         ###   ########.fr       */
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
t_gd	calculate_lighting(t_vector hit_point, t_vector normal,
			t_scene *scene, t_gd material_color, t_vector view_dir)
{
	t_gd		final_color;
	t_l			params;

	final_color = apply_ambient_light(material_color, scene->ambient);
	params.material_color = material_color;
	params.scene = scene;
	params.normal = normal;
	params.light_dir = vector_normalize(vector_sub(scene->light.coord.v,
				hit_point));
	params.view_dir = vector_normalize(vector_scale(view_dir, -1));
	if (!is_in_shadow(hit_point, normal, scene))
	{
		final_color = apply_diffuse_light(final_color, &params);
		final_color = apply_specular_light(final_color, &params);
	}
	final_color.r = fmin(255, fmax(0, final_color.r));
	final_color.g = fmin(255, fmax(0, final_color.g));
	final_color.b = fmin(255, fmax(0, final_color.b));
	return (final_color);
}

/**
 * @brief Renders the entire scene by tracing rays through each pixel.
 *
 * This function iterates through every pixel in the window, generates a camera
 * ray for each pixel, traces that ray through the scene to determine the 
 * color, and puts the resulting color to the pixel on screen. 
 * The viewport is calculated based on the window dimensions and aspect ratio.
 *
 * @param scene The scene containing all objects, camera,
 *        and lighting information.
 * @param data The miniRT data structure containing the MLX image buffer.
 */
void	render_scene(t_scene *scene, t_minirt *data)
{
	int			x;
	int			y;
	t_ray		ray;
	t_gd		color;
	t_viewport	viewport;

	viewport.width = WINDOW_WIDTH;
	viewport.height = WINDOW_HEIGHT;
	viewport.aspect_ratio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			ray = camera_ray(scene->camera, x, y, viewport);
			color = trace_ray(ray, scene);
			put_pixel(data, x, y, (color.r << 16) | (color.g << 8) | color.b);
			x++;
		}
		y++;
	}
}
