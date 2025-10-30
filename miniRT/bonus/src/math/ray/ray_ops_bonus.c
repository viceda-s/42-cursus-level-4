/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:07:56 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/25 18:28:53 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * Creates a new ray with given origin and direction
 * @param origin Starting point of the ray
 * @param direction Direction vector of the ray (should be normalized)
 * @return New ray structure
 */
t_ray	create_ray(t_vector origin, t_vector direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

/**
 * Gets a point along the ray at parameter t
 * Point = origin + t * direction
 * @param ray The ray
 * @param t Parameter along the ray (distance from origin)
 * @return Point on the ray
 */
t_vector	ray_at(t_ray ray, float t)
{
	t_vector	point;

	point = vector_add(ray.origin, vector_scale(ray.direction, t));
	return (point);
}

/**
 * Generates a ray from camera through a specific pixel
 * @param camera Camera configuration
 * @param x Pixel x coordinate (0 to width-1)
 * @param y Pixel y coordinate (0 to height-1)
 * @param viewport Viewport dimensions
 * @return Ray from camera through the pixel
 */
t_ray	camera_ray(t_camera camera, int x, int y, t_viewport viewport)
{
	t_vector	ray_direction;
	float		u;
	float		v;
	float		theta;
	float		h;

	u = (float)x / (float)(viewport.width - 1);
	v = (float)y / (float)(viewport.height - 1);
	theta = camera.fov * acos(-1.0f) / 180.0f;
	h = tanf(theta / 2.0f);
	viewport.height = 2.0f * h;
	viewport.width = viewport.aspect_ratio * viewport.height;
	ray_direction = camera.forward;
	ray_direction = vector_add(ray_direction,
			vector_scale(camera.right, (u - 0.5f) * viewport.width));
	ray_direction = vector_add(ray_direction,
			vector_scale(camera.up, (0.5f - v) * viewport.height));
	ray_direction = vector_normalize(ray_direction);
	return (create_ray(camera.position, ray_direction));
}
