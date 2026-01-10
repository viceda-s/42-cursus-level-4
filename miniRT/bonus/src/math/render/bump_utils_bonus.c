/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/03 16:12:06 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	build_tbn_from_normal(t_vector n, t_vector *t, t_vector *b)
{
	const t_vector	up = {0.0f, 1.0f, 0.0f};
	const t_vector	right = {1.0f, 0.0f, 0.0f};
	t_vector		ref;

	if (fabsf(vector_dot(n, (t_vector){0, 1, 0})) < 0.99f)
		ref = up;
	else
		ref = right;
	*t = vector_normalize(vector_cross(ref, n));
	*b = vector_cross(n, *t);
}

float	fracf(float x)
{
	return (x - floorf(x));
}

float	height_fn(float u, float v)
{
	const float	k = (float)(2.0 * M_PI);
	float		base;
	float		detail;

	base = sinf(k * u) * sinf(k * v);
	detail = 0.25f * sinf(k * 3.0f * u) * sinf(k * 3.0f * v);
	return (0.5f + 0.7f * (base + detail));
}
