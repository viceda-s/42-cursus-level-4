/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_aa_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg.>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:16:13 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/30 15:16:13 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "minirt_bonus.h"

/**
 * camera_ray_aa
 *
 * Build a camera ray for anti-aliased sampling.
 *
 * Compute normalized device coords from subpixel (x, y), apply aspect and
 * camera FOV, then combine camera basis (right, up, forward) into the
 * direction. Ray origin is camera.position and direction is normalized.
 *
 * @param camera   Camera with position, basis vectors and fov (degrees).
 * @param x        Subpixel x coordinate (may be fractional).
 * @param y        Subpixel y coordinate (may be fractional).
 * @param viewport Viewport with width, height and aspect_ratio.
 * @return t_ray   Ray with origin and normalized direction.
 * @note       Function is static (internal to the translation unit).
 */

static t_ray	camera_ray_aa(t_camera camera, float x, float y,
		t_viewport viewport)
{
	t_ray		ray;
	t_vector	dir;
	float		x_norm;
	float		y_norm;

	x_norm = (2 * x / viewport.width - 1)
		* viewport.aspect_ratio * tan(camera.fov * (M_PI / 180.0) / 2);
	y_norm = (1 - 2 * y / viewport.height)
		* tan(camera.fov * (M_PI / 180.0) / 2);
	dir = vector_add(vector_scale(camera.right, x_norm),
			vector_scale(camera.up, y_norm));
	dir = vector_add(dir, camera.forward);
	ray.origin = camera.position;
	ray.direction = vector_normalize(dir);
	return (ray);
}

/**
 * get_pixel_color_with_aa
 *
 * Compute averaged pixel color using stochastic anti-aliasing.
 *
 * Cast ANTI_ALIASING_SAMPLES rays with random subpixel jitter, accumulate
 * sample colors from trace_ray, average them, and return the result. Checker
 * flag is cleared on the returned color.
 *
 * @param scene    Scene pointer containing camera and world data.
 * @param x        Integer pixel x coordinate.
 * @param y        Integer pixel y coordinate.
 * @param viewport Viewport used for ray generation.
 * @return t_gd    Averaged color (r, g, b, checker=false).
 * @note       Uses rand() for jitter; seed externally for reproducible
 *             results.
 */

t_gd	get_pixel_color_with_aa(t_scene *scene, int x, int y,
		t_viewport viewport)
{
	t_gd	final_color;
	t_ray	ray;
	int		i;
	float	rgb[3];

	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	i = 0;
	while (i < ANTI_ALIASING_SAMPLES)
	{
		ray = camera_ray_aa(scene->camera, x + ((float)rand() \
/ (float)RAND_MAX), y + ((float)rand() / (float)RAND_MAX), viewport);
		final_color = trace_ray(ray, scene);
		rgb[0] += final_color.r;
		rgb[1] += final_color.g;
		rgb[2] += final_color.b;
		i++;
	}
	final_color.r = (int)(rgb[0] / ANTI_ALIASING_SAMPLES);
	final_color.g = (int)(rgb[1] / ANTI_ALIASING_SAMPLES);
	final_color.b = (int)(rgb[2] / ANTI_ALIASING_SAMPLES);
	final_color.checker = false;
	return (final_color);
}
