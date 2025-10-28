/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_geo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:02:15 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/27 18:08:04 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Calculates the dot product of two vectors.
 * 
 * The dot product is a scalar value that represents the projection of one
 * vector onto another. Returns positive if vectors point in the same general
 * direction, negative if opposite, and zero if orthogonal (perpendicular).
 * 
 * @param a The first vector.
 * @param b The second vector.
 * @return The dot product (scalar value) of vectors a and b.
 */
float	vector_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/**
 * @brief Calculates the cross product of two vectors.
 * 
 * The cross product produces a new vector that is perpendicular to both
 * input vectors. The magnitude of the result equals the area of the
 * parallelogram formed by the two vectors.
 * 
 * @param a The first vector.
 * @param b The second vector.
 * @return A vector perpendicular to both a and b.
 */
t_vector	vector_cross(t_vector a, t_vector b)
{
	t_vector	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

/**
 * @brief Calculates the length (magnitude) of a vector.
 * 
 * Uses the Euclidean distance formula to compute the magnitude of the vector
 * from the origin to the point (x, y, z).
 * 
 * @param v The vector whose length is to be calculated.
 * @return The length of the vector as a floating-point value.
 */
float	vector_length(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/**
 * @brief Normalizes a vector to unit length.
 * 
 * Converts the input vector to a unit vector (length = 1) that points in
 * the same direction. Returns the original vector if its length is zero
 * to avoid division by zero.
 * 
 * @param v The vector to be normalized.
 * @return A unit vector in the same direction as v,
 * or v itself if length is zero.
 */
t_vector	vector_normalize(t_vector v)
{
	float		len;
	t_vector	res;

	len = vector_length(v);
	if (len == 0)
		return (v);
	res.x = v.x / len;
	res.y = v.y / len;
	res.z = v.z / len;
	return (res);
}
