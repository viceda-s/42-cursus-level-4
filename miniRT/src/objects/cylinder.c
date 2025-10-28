/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:09:33 by rbaldin           #+#    #+#             */
/*   Updated: 2025/10/27 20:01:08 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static t_cy	*extracting_xyz_cy(t_scene *scene_coord, char **nums)
{
	t_cy	*cyli;

	cyli = (t_cy *)getting_latest_object(scene_coord, CYLINDER);
	if (!cyli)
		return (NULL);
	cyli->data.v.x = ft_atof_dp(nums);
	skip_comma(nums);
	cyli->data.v.y = ft_atof_dp(nums);
	skip_comma(nums);
	cyli->data.v.z = ft_atof_dp(nums);
	skipping_emptiness(nums);
	cyli->data.nov.x = ft_atof_dp(nums);
	skip_comma(nums);
	cyli->data.nov.y = ft_atof_dp(nums);
	skip_comma(nums);
	cyli->data.nov.z = ft_atof_dp(nums);
	cyli->data.nov = vector_normalize(cyli->data.nov);
	if (cyli->data.nov.x < -1.0 || cyli->data.nov.x > 1.0 || \
cyli->data.nov.y < -1.0 || cyli->data.nov.y > 1.0 || \
cyli->data.nov.z < -1.0 || cyli->data.nov.z > 1.0)
		return (NULL);
	return (cyli);
}

static int	extracting_rest_cy(t_cy *rest_cy, char **pcy)
{
	skipping_emptiness(pcy);
	rest_cy->d = ft_atof_dp(pcy);
	skipping_emptiness(pcy);
	rest_cy->h = ft_atof_dp(pcy);
	skipping_emptiness(pcy);
	rest_cy->data.r = ft_atoi_dp(pcy);
	skip_comma(pcy);
	rest_cy->data.g = ft_atoi_dp(pcy);
	skip_comma(pcy);
	rest_cy->data.b = ft_atoi_dp(pcy);
	if (rest_cy->data.r < 0 || rest_cy->data.r > 255 || rest_cy->data.b < 0
		|| rest_cy->data.b > 255 || rest_cy->data.g < 0
		|| rest_cy->data.g > 255 || rest_cy->d <= 0.0 || rest_cy->h <= 0.0)
	{
		return (1);
	}
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
	{
		return (1);
	}
	if (extracting_rest_cy(cyl, &ptr_cy))
		return (1);
	skipping_emptiness(&ptr_cy);
	if (*ptr_cy != '\0')
	{
		return (1);
	}
	return (0);
}
