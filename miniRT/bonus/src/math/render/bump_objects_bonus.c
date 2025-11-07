/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_objects_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:45:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/06 13:42:04 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	compute_sphere_uv_tbn(t_vector n, float uv[2], t_vector tbn[3])
{
	float	theta;
	float	phi;

	theta = atan2f(n.z, n.x);
	phi = acosf(fmaxf(-1.0f, fminf(1.0f, n.y)));
	uv[0] = (theta + 3.14159265f) / (2.0f * 3.14159265f);
	uv[1] = phi / 3.14159265f;
	tbn[0] = vector_normalize((t_vector){-sinf(theta), 0.0f, cosf(theta)});
	tbn[1] = vector_normalize((t_vector){-cosf(theta) * sinf(phi),
			cosf(phi), -sinf(theta) * sinf(phi)});
	tbn[2] = n;
}

void	apply_bump_sphere(t_shade *s, float str_scale, float freq_scale)
{
	t_sp			*sp;
	t_vector		tbn[3];
	float			uv[2];
	t_bump_params	bp;

	(void)freq_scale;
	sp = (t_sp *)s->hit_object;
	if (!sp->bump_map)
		return ;
	compute_sphere_uv_tbn(vector_normalize(vector_sub(s->hit_point,
				sp->coord_colours.v)), uv, tbn);
	bp = (t_bump_params){uv[0], uv[1], str_scale, {tbn[0], tbn[1], tbn[2]}};
	if (sp->bump_map->addr)
		s->normal = perturb_from_bump_map(sp->bump_map, bp, &s->bump_intensity);
}

void	apply_bump_plane(t_shade *s, float str_scale, float freq_scale)
{
	t_gd			*pl;
	t_vector		tbn[3];
	t_vector		p_local;
	float			uv[2];
	t_bump_params	bp;

	pl = (t_gd *)s->hit_object;
	if (!pl->bump_map)
		return ;
	tbn[2] = vector_normalize(pl->nov);
	build_tbn_from_normal(tbn[2], &tbn[0], &tbn[1]);
	p_local = vector_sub(s->hit_point, pl->v);
	uv[0] = vector_dot(p_local, tbn[0]) * freq_scale;
	uv[1] = vector_dot(p_local, tbn[1]) * freq_scale;
	bp = (t_bump_params){uv[0], uv[1], str_scale, {tbn[0], tbn[1], tbn[2]}};
	if (pl->bump_map->addr)
		s->normal = perturb_from_bump_map(pl->bump_map, bp, &s->bump_intensity);
}

void	apply_bump_cylinder(t_shade *s, float str_scale, float freq_scale)
{
	t_cy			*cy;
	t_vector		tbn[3];
	t_vector		p_local;
	float			uv[2];
	t_bump_params	bp;

	cy = (t_cy *)s->hit_object;
	if (!cy->bump_map)
		return ;
	tbn[2] = vector_normalize(cy->data.nov);
	build_tbn_from_normal(s->normal, &tbn[0], &tbn[1]);
	p_local = vector_sub(s->hit_point, cy->data.v);
	uv[0] = atan2f(vector_dot(p_local, tbn[0]), vector_dot(p_local, tbn[1]));
	uv[0] = uv[0] / (2.0f * 3.14159265f) + 0.5f;
	uv[1] = vector_dot(p_local, tbn[2]) * freq_scale;
	bp = (t_bump_params){uv[0], uv[1], str_scale, {tbn[0], tbn[1], tbn[2]}};
	if (cy->bump_map->addr)
		s->normal = perturb_from_bump_map(cy->bump_map, bp, &s->bump_intensity);
}

void	apply_bump_cube(t_shade *s, float str_scale, float freq_scale)
{
	t_cu			*cu;
	t_vector		tbn[3];
	float			uv[2];
	t_bump_params	bp;

	(void)freq_scale;
	cu = (t_cu *)s->hit_object;
	if (!cu->bump_map)
		return ;
	build_tbn_from_normal(s->normal, &tbn[0], &tbn[1]);
	tbn[2] = s->normal;
	map_cube_uv(s->hit_point, cu, &uv[0], &uv[1]);
	bp = (t_bump_params){uv[0], uv[1], str_scale, {tbn[0], tbn[1], tbn[2]}};
	if (cu->bump_map->addr)
		s->normal = perturb_from_bump_map(cu->bump_map, bp, &s->bump_intensity);
}
