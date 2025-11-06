/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:17:12 by rbaldin           #+#    #+#             */
/*   Updated: 2025/11/06 11:57:29 by viceda-s         ###   ########.fr       */
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

/* .rt example:
   cu    0,0,0      0,1,0   2.0   255,0,0
   id   v (centre)   nov    side  colours
*/

static	t_cu	*extracting_cube(t_scene *scene_co, char **n)
{
	t_cu		*cu;
	t_vector	tmp;

	cu = (t_cu *)getting_latest_object(scene_co, CUBE);
	if (!cu)
		return (NULL);
	tmp = parse_vector(n);
	cu->data.v = tmp;
	tmp = parse_vector(n);
	cu->data.nov = tmp;
	cu->data.nov = vector_normalize(tmp);
	skipping_emptiness(n);
	cu->side = ft_atof_dp(n);
	skipping_emptiness(n);
	if (parse_color(n, &cu->data))
		return (NULL);
	cu->texture = NULL;
	cu->bump_map = NULL;
	return (cu);
}

static	t_cu	*pre_calculating_cube(t_cu *cube)
{
	float		half_side;
	t_vector	world_up;
	t_vector	right;

	cube->param.axis = malloc(sizeof(t_vector) * 3);
	if (cube->param.axis == NULL)
		return (NULL);
	cube->param.axis[1] = vector_normalize(cube->data.nov);
	if (fabsf(cube->param.axis[1].y) > 0.999f)
		world_up = vector_create(1, 0, 0);
	else
		world_up = vector_create(0, 1, 0);
	right = vector_cross(world_up, cube->param.axis[1]);
	cube->param.axis[0] = vector_normalize(right);
	cube->param.axis[2] = vector_cross(cube->param.axis[1],
			cube->param.axis[0]);
	half_side = cube->side / 2.0f;
	cube->param.min_corner_bound = (t_vector){-half_side, -half_side, \
-half_side};
	cube->param.max_corner_bound = (t_vector){half_side, half_side, half_side};
	return (cube);
}

int	parsing_cube(t_scene *scene_cube, char *line_data_cube)
{
	char	*ptr_cu;
	t_cu	*cub;

	ptr_cu = line_data_cube;
	ptr_cu += 2;
	cub = extracting_cube(scene_cube, &ptr_cu);
	if (!cub)
		return (1);
	if (cub->data.nov.x < -1.0 || cub->data.nov.x > 1.0 || \
cub->data.nov.y < -1.0 || cub->data.nov.y > 1.0 || \
cub->data.nov.z < -1.0 || cub->data.nov.z > 1.0)
		return (1);
	parse_texture_map(&ptr_cu, &cub->texture);
	parse_bump_map(&ptr_cu, &cub->bump_map);
	parse_checker(&ptr_cu, &cub->data.checker);
	parse_bump(&ptr_cu, &cub->data.has_bump,
		&cub->data.bump_strength, &cub->data.bump_uv);
	skipping_emptiness(&ptr_cu);
	if (*ptr_cu != '\0')
		return (1);
	cub = pre_calculating_cube(cub);
	if (!cub)
		return (1);
	return (0);
}
