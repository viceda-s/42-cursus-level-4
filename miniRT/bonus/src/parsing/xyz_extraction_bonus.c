/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xyz_extraction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:22:34 by rbaldin           #+#    #+#             */
/*   Updated: 2025/10/26 18:24:20 by rbaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	extracting_xyz(t_scene *scene_coord, char **nums, char object_type)
{
	if (!scene_coord)
		return ;
	if ('c' == object_type)
	{
		scene_coord->camera.position.x = ft_atof_dp(nums);
		if (**nums == ',')
			(*nums)++;
		scene_coord->camera.position.y = ft_atof_dp(nums);
		if (**nums == ',')
			(*nums)++;
		scene_coord->camera.position.z = ft_atof_dp(nums);
	}
	else if ('l' == object_type)
	{
		scene_coord->light.coord.v.x = ft_atof_dp(nums);
		if (**nums == ',')
			(*nums)++;
		scene_coord->light.coord.v.y = ft_atof_dp(nums);
		if (**nums == ',')
			(*nums)++;
		scene_coord->light.coord.v.z = ft_atof_dp(nums);
	}
}

void	extracting_nov_cam(t_scene *scene_nov, char **novs)
{
	scene_nov->camera.forward.x = ft_atof_dp(novs);
	if (**novs == ',')
		(*novs)++;
	scene_nov->camera.forward.y = ft_atof_dp(novs);
	if (**novs == ',')
		(*novs)++;
	scene_nov->camera.forward.z = ft_atof_dp(novs);
}
