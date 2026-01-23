/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 11:18:11 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	save_player_pos(t_cub3d *cub, int y, int x)
{
	if (cub->parse.player_count > 0)
		err_exit(cub, ERR_MAP_PLAYER);
	cub->parse.player_dir = cub->map.grid[y][x];
	cub->parse.player_x = x;
	cub->parse.player_y = y;
	cub->parse.player_count++;
	cub->map.grid[y][x] = '0';
}

void	extract_player(t_cub3d *cub)
{
	int	y;
	int	x;

	y = -1;
	while (++y < cub->map.height)
	{
		x = -1;
		while (cub->map.grid[y][++x])
		{
			if (is_player_char(cub->map.grid[y][x]))
				save_player_pos(cub, y, x);
		}
	}
	if (cub->parse.player_count == 0)
		err_exit(cub, ERR_MAP_PLAYER);
}

void	validate_elements(t_cub3d *cub)
{
	int	i;

	if (!cub->parse.tex_paths[TEX_NORTH] || !cub->parse.tex_paths[TEX_SOUTH]
		|| !cub->parse.tex_paths[TEX_EAST] || !cub->parse.tex_paths[TEX_WEST])
		err_exit(cub, ERR_MISS_ELEMENT);
	i = 0;
	while (i < DOOR_FRAMES)
	{
		if (!cub->parse.tex_paths[TEX_DOOR_START + i])
			err_exit(cub, ERR_MISS_ELEMENT);
		i++;
	}
	if (!cub->parse.floor_set || !cub->parse.ceiling_set)
		err_exit(cub, ERR_MISS_ELEMENT);
	if (!cub->map.grid || cub->map.height == 0)
		err_exit(cub, ERR_MAP_EMPTY);
}
