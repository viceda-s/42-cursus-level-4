/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:43:16 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/27 18:07:48 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Creates a vector from three float components.
 *
 * Constructs a new 3D vector with the specified x, y, and z coordinates.
 *
 * @param x The x-component of the vector.
 * @param y The y-component of the vector.
 * @param z The z-component of the vector.
 * @return A new vector with the specified components.
 */
t_vector	vector_create(float x, float y, float z)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

/**
 * @brief Adds two vectors component-wise.
 *
 * Performs vector addition by adding the corresponding components of both
 * input vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return A new vector representing the sum of a and b.
 */
t_vector	vector_add(t_vector a, t_vector b)
{
	t_vector	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

/**
 * @brief Subtracts one vector from another component-wise.
 *
 * Performs vector subtraction by subtracting the components of vector b
 * from the corresponding components of vector a.
 *
 * @param a The vector to subtract from.
 * @param b The vector to subtract.
 * @return A new vector representing the difference (a - b).
 */
t_vector	vector_sub(t_vector a, t_vector b)
{
	t_vector	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

/**
 * @brief Scales a vector by a scalar value.
 *
 * Multiplies each component of the vector by the scalar value, effectively
 * scaling the vector's magnitude while maintaining its direction.
 *
 * @param v The vector to be scaled.
 * @param s The scalar multiplier.
 * @return A new vector with all components scaled by s.
 */
t_vector	vector_scale(t_vector v, float s)
{
	t_vector	res;

	res.x = v.x * s;
	res.y = v.y * s;
	res.z = v.z * s;
	return (res);
}
