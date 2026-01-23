/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:40:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 11:04:34 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	is_door(t_cub3d *cub, int x, int y)
{
	if (x < 0 || y < 0 || y >= cub->map.height)
		return (0);
	if (!cub->map.grid[y] || x >= (int)ft_strlen(cub->map.grid[y]))
		return (0);
	return (cub->map.grid[y][x] == 'D');
}

int	is_door_open(t_cub3d *cub, int x, int y)
{
	int	i;

	i = 0;
	while (i < cub->door_count)
	{
		if (cub->doors[i].x == x && cub->doors[i].y == y)
			return (cub->doors[i].state == DOOR_OPEN);
		i++;
	}
	return (0);
}

void	toggle_door(t_cub3d *cub)
{
	int	front_x;
	int	front_y;
	int	i;

	front_x = (int)(cub->player.pos_x + cub->player.dir_x);
	front_y = (int)(cub->player.pos_y + cub->player.dir_y);
	i = 0;
	while (i < cub->door_count)
	{
		if (cub->doors[i].x == front_x && cub->doors[i].y == front_y)
		{
			if (cub->doors[i].state == DOOR_CLOSED)
				cub->doors[i].state = DOOR_OPENING;
			else if (cub->doors[i].state == DOOR_OPEN)
				cub->doors[i].state = DOOR_CLOSING;
			return ;
		}
		i++;
	}
}

static void	update_door_animation(t_door *door)
{
	door->anim_timer++;
	if (door->anim_timer >= DOOR_FRAME_TIME)
	{
		door->anim_timer = 0;
		if (door->state == DOOR_OPENING)
		{
			door->anim_frame++;
			if (door->anim_frame >= DOOR_FRAMES - 1)
			{
				door->anim_frame = DOOR_FRAMES - 1;
				door->state = DOOR_OPEN;
			}
		}
		else if (door->state == DOOR_CLOSING)
		{
			door->anim_frame--;
			if (door->anim_frame <= 0)
			{
				door->anim_frame = 0;
				door->state = DOOR_CLOSED;
			}
		}
	}
}

void	update_doors(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < cub->door_count)
	{
		if (cub->doors[i].state == DOOR_OPENING
			|| cub->doors[i].state == DOOR_CLOSING)
			update_door_animation(&cub->doors[i]);
		i++;
	}
}
