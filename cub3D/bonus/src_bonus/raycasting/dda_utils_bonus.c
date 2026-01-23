/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:10:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 11:09:06 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	handle_door_hit(t_cub3d *cub, t_ray *ray)
{
	ray->door_map_x = ray->map_x;
	ray->door_map_y = ray->map_y;
	ray->door_side = ray->side;
	if (ray->side == 0)
		ray->door_perp_dist = (ray->map_x - cub->player.pos_x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->door_perp_dist = (ray->map_y - cub->player.pos_y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
	ray->hit_door = 1;
	return (1);
}

void	save_wall_behind_info(t_cub3d *cub, t_ray *ray)
{
	ray->wall_map_x = ray->map_x;
	ray->wall_map_y = ray->map_y;
	ray->wall_side = ray->side;
	if (ray->side == 0)
		ray->wall_perp_dist = (ray->map_x - cub->player.pos_x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->wall_perp_dist = (ray->map_y - cub->player.pos_y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
	ray->has_wall_behind = 1;
}
