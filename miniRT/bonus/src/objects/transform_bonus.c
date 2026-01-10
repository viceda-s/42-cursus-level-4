/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 00:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/06 11:01:32 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <threads.h>

#include "minirt_bonus.h"

/**
 * @brief Translates an object by a given offset.
 * 
 * This function modifies the position of a geometric object (plane, sphere,
 * or cylinder) by adding an offset vector to its current position.
 * 
 * @param obj A pointer to the object to be translated.
 * @param type The type of the object (PLANE, SPHERE, CYLINDER).
 * @param offset The vector representing the translation offset.
 */
void	translate_object(void *obj, t_object_type type, t_vector offset)
{
	t_gd	*pl;
	t_sp	*sp;
	t_cy	*cy;
	t_cu	*cu;

	if (type == PLANE)
	{
		pl = (t_gd *)obj;
		pl->v = vector_add(pl->v, offset);
	}
	else if (type == SPHERE)
	{
		sp = (t_sp *)obj;
		sp->coord_colours.v = vector_add(sp->coord_colours.v, offset);
	}
	else if (type == CYLINDER)
	{
		cy = (t_cy *)obj;
		cy->data.v = vector_add(cy->data.v, offset);
	}
	else if (type == CUBE)
	{
		cu = (t_cu *)obj;
		cu->data.v = vector_add(cu->data.v, offset);
	}
}

static void	apply_rotation(t_vector *nov, t_rotation rot)
{
	if (rot.pitch != 0)
		*nov = rotate_axis(*nov, rot.pitch, 0);
	if (rot.yaw != 0)
		*nov = rotate_axis(*nov, rot.yaw, 1);
	if (rot.roll != 0)
		*nov = rotate_axis(*nov, rot.roll, 2);
	*nov = vector_normalize(*nov);
}

/**
 * @brief Rotates an object around the X, Y, and Z axes.
 * 
 * This function modifies the orientation of an object (plane or cylinder)
 * by applying rotations. Spheres are not rotated as it has no visual effect.
 * It uses the `rotate_axis` function to perform the rotation.
 * 
 * @param obj A pointer to the object to be rotated.
 * @param type The type of the object (PLANE, CYLINDER).
 * @param rot A t_rotation struct containing pitch, yaw, and roll angles.
 */
void	rotate_object(void *obj, t_object_type type, t_rotation rot)
{
	t_vector	*normal_to_rotate;

	normal_to_rotate = NULL;
	if (type == PLANE)
		normal_to_rotate = &((t_gd *)obj)->nov;
	else if (type == CYLINDER)
		normal_to_rotate = &((t_cy *)obj)->data.nov;
	else if (type == CUBE)
		normal_to_rotate = &((t_cu *)obj)->data.nov;
	if (normal_to_rotate)
		apply_rotation(normal_to_rotate, rot);
}

/**
 * @brief Translates a light by a given offset.
 * 
 * @param light A pointer to the light to be translated.
 * @param offset The vector representing the translation offset.
 */
void	translate_light(t_l *light, t_vector offset)
{
	light->coord.v = vector_add(light->coord.v, offset);
}

/*
 * Example for rotating a directional light.
 * This assumes you have a way to distinguish light types and that your
 * light struct `t_l` has a direction vector.
 *
void	rotate_light(t_l *light, float pitch, float yaw, float roll)
{
	// if (light->type == DIRECTIONAL) // Example check
	// {
	// 	if (pitch != 0)
	// 		light->direction = rotate_axis(light->direction, pitch, 0);
	// 	if (yaw != 0)
	// 		light->direction = rotate_axis(light->direction, yaw, 1);
	// 	if (roll != 0)
	// 		light->direction = rotate_axis(light->direction, roll, 2);
	// 	light->direction = vector_normalize(light->direction);
	// }
}
*/
