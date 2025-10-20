/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:07:56 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/20 08:08:52 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
    t_vector	pixel_world;
    t_vector	ray_direction;
    float		u;
    float		v;

    // Convert pixel coordinates to normalized device coordinates (-1 to 1)
    u = (2.0f * x / (float)viewport.width) - 1.0f;
    v = 1.0f - (2.0f * y / (float)viewport.height);

    // Apply aspect ratio and field of view
    u *= viewport.aspect_ratio * tanf(camera.fov * acos(-1.0f) / 360.0f);
    v *= tanf(camera.fov * acos(-1.0f) / 360.0f);

    // Calculate pixel position in world space
    pixel_world = vector_add(camera.position, 
        vector_add(vector_scale(camera.right, u),
            vector_scale(camera.up, v)));
    pixel_world = vector_add(pixel_world, camera.forward);

    // Calculate ray direction from camera to pixel
    ray_direction = vector_subtract(pixel_world, camera.position);
    ray_direction = vector_normalize(ray_direction);

    return (create_ray(camera.position, ray_direction));
}
