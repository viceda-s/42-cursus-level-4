/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:17:12 by rbaldin           #+#    #+#             */
/*   Updated: 2025/11/06 13:54:35 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static float	get_sign(float value)
{
	if (value > 0)
		return (1.0f);
	return (-1.0f);
}

static t_vector	check_face_normal(t_cu *cube, t_vector p, float half, float eps)
{
	if (fabsf(fabsf(p.x) - half) < eps)
		return (vector_scale(cube->param.axis[0], get_sign(p.x)));
	if (fabsf(fabsf(p.y) - half) < eps)
		return (vector_scale(cube->param.axis[1], get_sign(p.y)));
	if (fabsf(fabsf(p.z) - half) < eps)
		return (vector_scale(cube->param.axis[2], get_sign(p.z)));
	if (fabsf(p.x) > fabsf(p.y) && fabsf(p.x) > fabsf(p.z))
		return (vector_scale(cube->param.axis[0], get_sign(p.x)));
	else if (fabsf(p.y) > fabsf(p.z))
		return (vector_scale(cube->param.axis[1], get_sign(p.y)));
	else
		return (vector_scale(cube->param.axis[2], get_sign(p.z)));
}

t_vector	get_cube_normal(void *ob_data, t_vector hit_pt)
{
	t_cu		*cube;
	t_vector	local_hit_pt;
	t_vector	p;
	float		half;
	float		eps;

	cube = (t_cu *)ob_data;
	local_hit_pt = vector_sub(hit_pt, cube->data.v);
	p.x = vector_dot(local_hit_pt, cube->param.axis[0]);
	p.y = vector_dot(local_hit_pt, cube->param.axis[1]);
	p.z = vector_dot(local_hit_pt, cube->param.axis[2]);
	half = cube->side / 2.0f;
	eps = 0.001f;
	return (check_face_normal(cube, p, half, eps));
}
