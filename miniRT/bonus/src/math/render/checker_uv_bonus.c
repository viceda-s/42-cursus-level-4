/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_uv_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:20:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/06 13:00:47 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	map_cube_face(t_vector local, t_uv_params *params, int axis)
{
	if (axis == 0)
	{
		params->uv[0] = (local.z / params->half + 1.0f) * 0.5f;
		params->uv[1] = (local.y / params->half + 1.0f) * 0.5f;
	}
	else if (axis == 1)
	{
		params->uv[0] = (local.x / params->half + 1.0f) * 0.5f;
		params->uv[1] = (local.z / params->half + 1.0f) * 0.5f;
	}
	else
	{
		params->uv[0] = (local.x / params->half + 1.0f) * 0.5f;
		params->uv[1] = (local.y / params->half + 1.0f) * 0.5f;
	}
}

static void	select_cube_face(t_vector local, t_uv_params *params)
{
	if (fabsf(params->abs_x - params->half) < 0.01f)
		map_cube_face(local, params, 0);
	else if (fabsf(params->abs_y - params->half) < 0.01f)
		map_cube_face(local, params, 1);
	else if (fabsf(params->abs_z - params->half) < 0.01f)
		map_cube_face(local, params, 2);
	else if (params->abs_x > params->abs_y && params->abs_x > params->abs_z)
		map_cube_face(local, params, 0);
	else if (params->abs_y > params->abs_z)
		map_cube_face(local, params, 1);
	else
		map_cube_face(local, params, 2);
}

void	map_cube_uv(t_vector p, t_cu *cube, float *u, float *v)
{
	t_vector	local;
	t_vector	rel;
	t_uv_params	params;

	rel = vector_sub(p, cube->data.v);
	local.x = vector_dot(rel, cube->param.axis[0]);
	local.y = vector_dot(rel, cube->param.axis[1]);
	local.z = vector_dot(rel, cube->param.axis[2]);
	params.half = cube->side / 2.0f;
	params.abs_x = fabsf(local.x);
	params.abs_y = fabsf(local.y);
	params.abs_z = fabsf(local.z);
	select_cube_face(local, &params);
	*u = params.uv[0];
	*v = params.uv[1];
}
