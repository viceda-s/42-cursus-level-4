/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_geo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:02:15 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/20 07:46:37 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	vector_dot(t_vector a, t_vector b) // Return the dot product (scalar) of two vectors
// if vectors are orthogonal, same sense (+) or different sense (-)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	vector_cross(t_vector a, t_vector b) // Return the cross product (vector) of two vectors
{
	t_vector	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

float	vector_length(t_vector v) // Return the magnitude (length) of a vector using Euclidean distance
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector	vector_normalize(t_vector v) // converts vector v to a unit vector
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