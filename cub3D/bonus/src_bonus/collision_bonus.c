/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:45:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/12/02 16:33:13 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	is_wall_bonus(t_cub3d *cub, double x, double y)
{
	int		map_x;
	int		map_y;
	char	tile;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0)
		return (1);
	if (map_y >= cub->map.height)
		return (1);
	if (!cub->map.grid[map_y])
		return (1);
	if (map_x >= (int)ft_strlen(cub->map.grid[map_y]))
		return (1);
	tile = cub->map.grid[map_y][map_x];
	if (tile == '1')
		return (1);
	if (tile == 'D' && !is_door_open(cub, map_x, map_y))
		return (1);
	return (0);
}