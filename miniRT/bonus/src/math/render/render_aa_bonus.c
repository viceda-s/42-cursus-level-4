/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_aa_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:16:13 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/03 16:12:06 by viceda-s         ###   ########.fr       */
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

	ray = camera_ray_aa(scene->camera, x + 0.5f, y + 0.5f, viewport);
	final_color = trace_ray(ray, scene);
	final_color.checker = false;
	return (final_color);
}

static void	accumulate_sample(t_aa_params *p, int i, int samples, float *data)
{
	float	offset[2];
	float	weight;
	t_ray	ray;
	t_gd	color;

	stratified_sample(i, samples, &offset[0], &offset[1]);
	weight = gaussian_weight(offset[0], offset[1], 0.5f, 0.5f);
	ray = camera_ray_aa(p->scene->camera, p->x + offset[0],
			p->y + offset[1], p->viewport);
	color = trace_ray(ray, p->scene);
	data[0] += color.r * weight;
	data[1] += color.g * weight;
	data[2] += color.b * weight;
	data[3] += weight;
}

t_gd	get_pixel_color_aa_quality(t_aa_params params, int samples)
{
	t_gd	final_color;
	float	data[4];
	int		i;

	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
	i = 0;
	while (i < samples)
	{
		accumulate_sample(&params, i, samples, data);
		i++;
	}
	final_color.r = (int)(data[0] / data[3]);
	final_color.g = (int)(data[1] / data[3]);
	final_color.b = (int)(data[2] / data[3]);
	final_color.checker = false;
	return (final_color);
}
