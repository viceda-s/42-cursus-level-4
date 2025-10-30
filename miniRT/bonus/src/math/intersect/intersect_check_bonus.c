/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 08:38:10 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/27 08:44:25 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * @brief Checks for intersection between a ray and all spheres in the scene.
 * 
 * This function finds the closest sphere intersection and updates the hit info
 * if the intersection distance is valid (greater than 0.001f).
 * 
 * @param ray The ray being cast.
 * @param scene The scene containing all sphere objects.
 * @param info Pointer to the hit information structure to be updated.
 */
static void	check_sphere_intersection(t_ray ray, t_scene *scene,
		t_hit *info)
{
	t_sp	*hit_sphere;
	float	sphere_t;

	sphere_t = find_closest_sphere_intersection(ray, scene, &hit_sphere);
	if (sphere_t > 0.001f)
	{
		info->closest_t = sphere_t;
		*info->hit_object = hit_sphere;
		*info->hit_type = SPHERE;
	}
}

/**
 * @brief Checks for intersection between a ray and all planes in the scene.
 * 
 * This function finds the closest plane intersection and updates the hit info
 * if the intersection distance is valid and closer than any previous hit.
 * 
 * @param ray The ray being cast.
 * @param scene The scene containing all plane objects.
 * @param info Pointer to the hit information structure to be updated.
 */
static void	check_plane_intersection(t_ray ray, t_scene *scene,
		t_hit *info)
{
	t_gd	*hit_plane;
	float	plane_t;

	plane_t = find_closest_plane_intersection(ray, scene, &hit_plane);
	if (plane_t > 0.001f && (info->closest_t < 0 || plane_t < info->closest_t))
	{
		info->closest_t = plane_t;
		*info->hit_object = hit_plane;
		*info->hit_type = PLANE;
	}
}

/**
 * @brief Checks for intersection between a ray and all cylinders in the scene.
 * 
 * This function finds the closest cylinder intersection and updates the hit info
 * if the intersection distance is valid and closer than any previous hit.
 * 
 * @param ray The ray being cast.
 * @param scene The scene containing all cylinder objects.
 * @param info Pointer to the hit information structure to be updated.
 */
static void	check_cylinder_intersection(t_ray ray, t_scene *scene,
		t_hit *info)
{
	t_cy	*hit_cylinder;
	float	cylinder_t;

	cylinder_t = find_closest_cylinder_intersection(ray, scene, &hit_cylinder);
	if (cylinder_t > 0.001f
		&& (info->closest_t < 0 || cylinder_t < info->closest_t))
	{
		info->closest_t = cylinder_t;
		*info->hit_object = hit_cylinder;
		*info->hit_type = CYLINDER;
	}
}

/**
 * @brief Finds the closest intersection of a ray with any object in the scene.
 * 
 * This function iterates through all spheres, planes, and cylinders to find the 
 * single closest point of intersection.
 * 
 * @param ray The ray being cast.
 * @param scene The scene containing all objects.
 * @param hit_object A pointer to a void pointer, which will be updated to 
 * point to the object that was hit.
 * @param hit_type A pointer to an object type enum, which will be updated with 
 * the type of the object that was hit.
 * @return The distance 't' to the closest intersection, or a negative value 
 * if no intersection occurs.
 */
float	find_closest_intersection(t_ray ray, t_scene *scene, void **hit_object,
			t_object_type *hit_type)
{
	t_hit	info;

	info.closest_t = -1.0f;
	info.hit_object = hit_object;
	info.hit_type = hit_type;
	*info.hit_object = NULL;
	check_sphere_intersection(ray, scene, &info);
	check_plane_intersection(ray, scene, &info);
	check_cylinder_intersection(ray, scene, &info);
	return (info.closest_t);
}
