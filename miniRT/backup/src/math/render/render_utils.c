/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:21:32 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/27 19:10:23 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Retrieves the material color from an object based on its type.
 * 
 * Extracts the RGB color information from the object's data structure.
 * Different object types store their color in different fields.
 * 
 * @param object_data Pointer to the object's data structure.
 * @param type The type of the object (SPHERE, PLANE, or CYLINDER).
 * @return The material color as a t_gd struct, or a default black color if
 *         the type is unknown.
 */
static t_gd	getting_material_color(void *object_data, t_object_type type)
{
	if (type == SPHERE)
		return (((t_sp *)object_data)->coord_colours);
	else if (type == PLANE)
		return (*((t_gd *)object_data));
	else if (type == CYLINDER)
		return (((t_cy *)object_data)->data);
	return ((t_gd){0, 0, 0, {0, 0, 0}, {0, 0, 0}});
}

/**
 * @brief Calculates the surface normal at a point on a sphere.
 * 
 * The normal at any point on a sphere is the normalized vector from the
 * sphere's center to that point.
 * 
 * @param object_data Pointer to the sphere object data.
 * @param hit_point The point on the sphere's surface
 * where intersection occurred.
 * @return The normalized surface normal vector at the hit point.
 */
static t_vector	get_sphere_normal(void *object_data, t_vector hit_point)
{
	t_sp	*sphere;

	sphere = (t_sp *)object_data;
	return (vector_normalize(vector_sub(hit_point, sphere->coord_colours.v)));
}

/**
 * @brief Calculates the surface normal at a point on a cylinder.
 * 
 * Computes the perpendicular distance from the hit point to the cylinder's
 * central axis to determine the surface normal.
 * 
 * @param object_data Pointer to the cylinder object data.
 * @param hit_point The point on the cylinder's surface
 * where intersection occurred.
 * @return The normalized surface normal vector at the hit point.
 */
static t_vector	get_cylinder_normal(void *object_data, t_vector hit_point)
{
	t_cy		*cylinder;
	t_vector	oc;
	float		m;
	t_vector	normal;

	cylinder = (t_cy *)object_data;
	oc = vector_sub(hit_point, cylinder->data.v);
	m = vector_dot(oc, cylinder->data.nov);
	normal = vector_sub(oc, vector_scale(cylinder->data.nov, m));
	return (vector_normalize(normal));
}

/**
 * @brief Gets the surface normal for any object type at a given hit point.
 * 
 * Dispatches to the appropriate normal calculation function based on the
 * object type.
 * 
 * @param object_data Pointer to the object's data structure.
 * @param type The type of the object (SPHERE, PLANE, or CYLINDER).
 * @param hit_point The point on the object's surface
 * where intersection occurred.
 * @return The normalized surface normal vector at the hit point, or a default
 *         upward vector if the type is unknown.
 */
static t_vector	getting_normal_for_object(void *object_data,
			t_object_type type, t_vector hit_point)
{
	if (type == SPHERE)
		return (get_sphere_normal(object_data, hit_point));
	else if (type == PLANE)
		return (vector_normalize(((t_gd *)object_data)->nov));
	else if (type == CYLINDER)
		return (get_cylinder_normal(object_data, hit_point));
	return ((t_vector){0, 1, 0});
}

/**
 * @brief Traces a ray through the scene and computes the color.
 * 
 * Finds the closest intersection point along the ray, calculates the surface
 * normal, and applies lighting to determine the final pixel color. Returns
 * a background color if no intersection is found.
 * 
 * @param ray The ray being traced through the scene.
 * @param scene The scene containing all objects and lighting.
 * @return The computed color for the ray, or a default background color
 *         if no intersection occurs.
 */
t_gd	trace_ray(t_ray ray, t_scene *scene)
{
	float			t;
	void			*hit_object;
	t_object_type	hit_type;
	t_vector		hit_point;
	t_vector		normal;

	t = find_closest_intersection(ray, scene, &hit_object, &hit_type);
	if (t > 0)
	{
		hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
		normal = getting_normal_for_object(hit_object, hit_type, hit_point);
		return (calculate_lighting(hit_point, normal, scene,
				getting_material_color(hit_object, hit_type)));
	}
	return ((t_gd){50, 50, 100, {0, 0, 0}, {0, 0, 0}});
}
