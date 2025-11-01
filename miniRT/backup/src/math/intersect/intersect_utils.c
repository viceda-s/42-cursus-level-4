/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 08:38:10 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/25 18:23:54 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Finds the closest intersection of a ray with any sphere in the scene.
 * 
 * @param ray The ray being cast.
 * @param scene The scene containing the objects.
 * @param hit_sphere A pointer to a sphere pointer, which will be updated to 
 * point to the sphere that was hit.
 * @return The distance 't' to the closest intersection, or a negative value 
 * if no intersection occurs.
 */
float	find_closest_sphere_intersection(t_ray ray, t_scene *scene,
			t_sp **hit_sphere)
{
	t_list		*current;
	t_objects	*obj;
	t_sp		*sphere;
	float		closest_t;
	float		t;

	closest_t = -1.0f;
	*hit_sphere = NULL;
	current = scene->objects_list;
	while (current)
	{
		obj = (t_objects *)current->content;
		if (obj->type == SPHERE)
		{
			sphere = (t_sp *)obj->object_data;
			t = intersect_sphere(ray, sphere);
			if (t > 0.001f && (closest_t < 0 || t < closest_t))
			{
				closest_t = t;
				*hit_sphere = sphere;
			}
		}
		current = current->next;
	}
	return (closest_t);
}

/**
 * @brief Finds the closest intersection of a ray with any plane in the scene.
 * 
 * @param ray The ray being cast.
 * @param scene The scene containing the objects.
 * @param hit_plane A pointer to a plane pointer, which will be updated to 
 * point to the plane that was hit.
 * @return The distance 't' to the closest intersection, or a negative value 
 * if no intersection occurs.
 */
float	find_closest_plane_intersection(t_ray ray, t_scene *scene,
			t_gd **hit_plane)
{
	t_list		*current;
	t_objects	*obj;
	t_gd		*plane;
	float		closest_t;
	float		t;

	closest_t = -1.0f;
	*hit_plane = NULL;
	current = scene->objects_list;
	while (current)
	{
		obj = (t_objects *)current->content;
		if (obj->type == PLANE)
		{
			plane = (t_gd *)obj->object_data;
			t = intersect_plane(ray, plane);
			if (t > 0.001f && (closest_t < 0 || t < closest_t))
			{
				closest_t = t;
				*hit_plane = plane;
			}
		}
		current = current->next;
	}
	return (closest_t);
}

/**
 * @brief Finds the closest intersection of a ray with any cylinder in the scene.
 * 
 * @param ray The ray being cast.
 * @param scene The scene containing the objects.
 * @param hit_cylinder A pointer to a cylinder pointer, which will be updated to 
 * point to the cylinder that was hit.
 * @return The distance 't' to the closest intersection, or a negative value 
 * if no intersection occurs.
 */
float	find_closest_cylinder_intersection(t_ray ray, t_scene *scene,
			t_cy **hit_cylinder)
{
	t_list		*current;
	t_objects	*obj;
	t_cy		*cylinder;
	float		closest_t;
	float		t;

	closest_t = -1.0f;
	*hit_cylinder = NULL;
	current = scene->objects_list;
	while (current)
	{
		obj = (t_objects *)current->content;
		if (obj->type == CYLINDER)
		{
			cylinder = (t_cy *)obj->object_data;
			t = intersect_cylinder(ray, cylinder);
			if (t > 0.001f && (closest_t < 0 || t < closest_t))
			{
				closest_t = t;
				*hit_cylinder = cylinder;
			}
		}
		current = current->next;
	}
	return (closest_t);
}
