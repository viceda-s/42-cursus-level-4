/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_apply_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/05 19:53:21 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_vector	calc_perturbed_normal(float h, float hx, float hy,
	float strength)
{
	t_vector	n_tan;
	float		scale;

	scale = 3.0f;
	n_tan.x = -strength * hx * scale / 0.002f;
	n_tan.y = -strength * hy * scale / 0.002f;
	n_tan.z = 1.0f;
	(void)h;
	return (n_tan);
}

t_vector	perturb_from_bump_map(t_texture *bump_map, t_bump_params params,
	float *out_intensity)
{
	float		h;
	float		hx;
	float		hy;
	t_vector	n_tan;
	t_vector	n_world;

	h = get_bump_height(bump_map, params.u, params.v);
	hx = get_bump_height(bump_map, params.u + 0.002f, params.v) - h;
	hy = get_bump_height(bump_map, params.u, params.v + 0.002f) - h;
	n_tan = calc_perturbed_normal(h, hx, hy, params.strength);
	*out_intensity = fminf(1.0f, sqrtf(hx * hx + hy * hy)
			* params.strength * 2.0f);
	n_tan = vector_normalize(n_tan);
	n_world.x = params.tbn[0].x * n_tan.x + params.tbn[1].x * n_tan.y
		+ params.tbn[2].x * n_tan.z;
	n_world.y = params.tbn[0].y * n_tan.x + params.tbn[1].y * n_tan.y
		+ params.tbn[2].y * n_tan.z;
	n_world.z = params.tbn[0].z * n_tan.x + params.tbn[1].z * n_tan.y
		+ params.tbn[2].z * n_tan.z;
	return (vector_normalize(n_world));
}

t_vector	perturb_from_height(t_bump_params params, float *out_intensity)
{
	float		h;
	float		hx;
	float		hy;
	t_vector	n_tan;
	t_vector	n_world;

	h = height_fn(params.u, params.v);
	hx = height_fn(params.u + 0.002f, params.v) - h;
	hy = height_fn(params.u, params.v + 0.002f) - h;
	n_tan = calc_perturbed_normal(h, hx, hy, params.strength);
	*out_intensity = fminf(1.0f, sqrtf(hx * hx + hy * hy)
			* params.strength * 2.0f);
	n_tan = vector_normalize(n_tan);
	n_world.x = params.tbn[0].x * n_tan.x + params.tbn[1].x * n_tan.y
		+ params.tbn[2].x * n_tan.z;
	n_world.y = params.tbn[0].y * n_tan.x + params.tbn[1].y * n_tan.y
		+ params.tbn[2].y * n_tan.z;
	n_world.z = params.tbn[0].z * n_tan.x + params.tbn[1].z * n_tan.y
		+ params.tbn[2].z * n_tan.z;
	return (vector_normalize(n_world));
}
