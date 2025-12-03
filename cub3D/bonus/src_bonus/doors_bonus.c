/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:40:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/12/02 16:33:13 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	count_doors(t_cub3d *cub)
{
	int	count;
	int	x;
	int	y;

	count = 0;
	y = 0;
	while (y < cub->map.height)
	{
		x = 0;
		while (cub->map.grid[y] && cub->map.grid[y][x])
		{
			if (cub->map.grid[y][x] == 'D')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	add_door(t_cub3d *cub, int x, int y, int *index)
{
	cub->doors[*index].x = x;
	cub->doors[*index].y = y;
	cub->doors[*index].state = DOOR_CLOSED;
	(*index)++;
}

void	init_doors(t_cub3d *cub)
{
	int	x;
	int	y;
	int	index;

	cub->door_count = count_doors(cub);
	if (cub->door_count == 0)
	{
		cub->doors = NULL;
		return ;
	}
	cub->doors = malloc(sizeof(t_door) * cub->door_count);
	if (!cub->doors)
		err_exit(cub, ERR_MALLOC);
	index = 0;
	y = 0;
	while (y < cub->map.height)
	{
		x = 0;
		while (cub->map.grid[y] && cub->map.grid[y][x])
		{
			if (cub->map.grid[y][x] == 'D')
				add_door(cub, x, y, &index);
			x++;
		}
		y++;
	}
}

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
				cub->doors[i].state = DOOR_OPEN;
			else
				cub->doors[i].state = DOOR_CLOSED;
			return ;
		}
		i++;
	}
}