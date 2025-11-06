/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cube_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:22:46 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/05 20:29:46 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	get_slab_intersection(t_internal *slab, float *tn, float *tf)
{
	float	t_1;
	float	t_2;

	if (fabsf(slab->direction) < 1e-8f)
	{
		if (slab->origin < slab->min || slab->origin > slab->max)
		{
			*tn = INFINITY;
			*tf = -INFINITY;
		}
		return ;
	}
	t_1 = (slab->min - slab->origin) / slab->direction;
	t_2 = (slab->max - slab->origin) / slab->direction;
	if (t_1 > t_2)
	{
		*tn = fmaxf(*tn, t_2);
		*tf = fminf(*tf, t_1);
	}
	else
	{
		*tn = fmaxf(*tn, t_1);
		*tf = fminf(*tf, t_2);
	}
}

float	intersect_cube(t_ray ray, t_cu *cube)
{
	t_vector	p;
	float		tnear;
	float		tfar;
	float		half;
	t_internal	slab;

	p = vector_sub(ray.origin, cube->data.v);
	tnear = -INFINITY;
	tfar = INFINITY;
	half = cube->side / 2.0f;
	slab = (t_internal){NULL, {0, 0, 0}, {0, 0, 0}, 0, 0,
		vector_dot(p, cube->param.axis[0]),
		vector_dot(ray.direction, cube->param.axis[0]), -half, half, 0, 0, 0};
	get_slab_intersection(&slab, &tnear, &tfar);
	if (tnear > tfar)
		return (-1.0f);
	slab.origin = vector_dot(p, cube->param.axis[1]);
	slab.direction = vector_dot(ray.direction, cube->param.axis[1]);
	get_slab_intersection(&slab, &tnear, &tfar);
	if (tnear > tfar)
		return (-1.0f);
	slab.origin = vector_dot(p, cube->param.axis[2]);
	slab.direction = vector_dot(ray.direction, cube->param.axis[2]);
	get_slab_intersection(&slab, &tnear, &tfar);
	if (tnear > tfar || tfar < 0.001f)
		return (-1.0f);
	if (tnear > 0.001f)
		return (tnear);
	return (tfar);
}
