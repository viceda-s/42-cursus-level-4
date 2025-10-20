/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:43:16 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/20 07:45:20 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	vector_create(float x, float y, float z) // Create a vector from 3 float components
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vector	vector_add(t_vector a, t_vector b) // Addition of the coordinates
{
	t_vector	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vector	vector_sub(t_vector a, t_vector b) // Subtraction of the coordinates
{
	t_vector	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

t_vector	vector_scale(t_vector v, double s) // Multiplies each component of vector v by scalar s, returning a scaled vector
{
	t_vector	res;

	res.x = v.x * s;
	res.y = v.y * s;
	res.z = v.z * s;
	return (res);
}