/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:09:33 by rbaldin           #+#    #+#             */
/*   Updated: 2025/11/06 11:57:27 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_cy	*extracting_xyz_cy(t_scene *scene_coord, char **nums)
{
	t_cy		*cyli;
	t_vector	tmp;

	cyli = (t_cy *)getting_latest_object(scene_coord, CYLINDER);
	if (!cyli)
		return (NULL);
	tmp = parse_vector(nums);
	cyli->data.v = tmp;
	tmp = parse_vector(nums);
	cyli->data.nov = vector_normalize(tmp);
	if (cyli->data.nov.x < -1.0 || cyli->data.nov.x > 1.0 || \
cyli->data.nov.y < -1.0 || cyli->data.nov.y > 1.0 || \
cyli->data.nov.z < -1.0 || cyli->data.nov.z > 1.0)
		return (NULL);
	return (cyli);
}

static int	extracting_rest_cy(t_cy *rest_cy, char **pcy)
{
	if (!rest_cy || !pcy)
		return (1);
	rest_cy->d = ft_atof_dp(pcy);
	skipping_emptiness(pcy);
	rest_cy->h = ft_atof_dp(pcy);
	skipping_emptiness(pcy);
	if (parse_color(pcy, &rest_cy->data))
		return (1);
	if (rest_cy->d <= 0.0f || rest_cy->h <= 0.0f)
		return (1);
	return (0);
}

int	parsing_cylinder(t_scene *scene_cylinder, char *line_data_cylinder)
{
	char	*ptr_cy;
	t_cy	*cyl;

	ptr_cy = line_data_cylinder;
	ptr_cy += 2;
	cyl = extracting_xyz_cy(scene_cylinder, &ptr_cy);
	if (!cyl)
		return (1);
	if (extracting_rest_cy(cyl, &ptr_cy))
		return (1);
	parse_texture_map(&ptr_cy, &cyl->texture);
	parse_bump_map(&ptr_cy, &cyl->bump_map);
	parse_checker(&ptr_cy, &cyl->data.checker);
	parse_bump(&ptr_cy, &cyl->data.has_bump,
		&cyl->data.bump_strength, &cyl->data.bump_uv);
	skipping_emptiness(&ptr_cy);
	if (*ptr_cy != '\0')
		return (1);
	return (0);
}
