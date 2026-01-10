/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/12/02 16:10:14 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_north_south(t_cub3d *cub)
{
	if (cub->parse.player_dir == 'N')
	{
		cub->player.dir_y = -1;
		cub->player.plane_x = 0.66;
	}
	else if (cub->parse.player_dir == 'S')
	{
		cub->player.dir_y = 1;
		cub->player.plane_x = -0.66;
	}
}

static void	set_east_west(t_cub3d *cub)
{
	if (cub->parse.player_dir == 'E')
	{
		cub->player.dir_x = 1;
		cub->player.plane_y = 0.66;
	}
	else if (cub->parse.player_dir == 'W')
	{
		cub->player.dir_x = -1;
		cub->player.plane_y = -0.66;
	}
}

void	init_player_direction(t_cub3d *cub)
{
	cub->player.dir_x = 0;
	cub->player.dir_y = 0;
	cub->player.plane_x = 0;
	cub->player.plane_y = 0;
	set_north_south(cub);
	set_east_west(cub);
}

void	init_player(t_cub3d *cub)
{
	cub->player.pos_x = cub->parse.player_x + 0.5;
	cub->player.pos_y = cub->parse.player_y + 0.5;
	cub->player.move_speed = MOVE_SPEED;
	cub->player.rot_speed = ROT_SPEED;
	init_player_direction(cub);
}
