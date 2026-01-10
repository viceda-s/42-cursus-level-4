/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/12/02 16:33:13 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	validate_elements(t_cub3d *cub)
{
	if (!cub->parse.tex_paths[TEX_NORTH] || !cub->parse.tex_paths[TEX_SOUTH]
		|| !cub->parse.tex_paths[TEX_EAST] || !cub->parse.tex_paths[TEX_WEST])
		err_exit(cub, ERR_MISS_ELEMENT);
	if (!cub->parse.floor_set || !cub->parse.ceiling_set)
		err_exit(cub, ERR_MISS_ELEMENT);
	if (!cub->map.grid || cub->map.height == 0)
		err_exit(cub, ERR_MAP_EMPTY);
}

static int	is_valid_char_bonus(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'D');
}

static int	check_surrounded(t_cub3d *cub, int y, int x)
{
	if (y == 0 || y == cub->map.height - 1)
		return (0);
	if (x == 0 || x >= (int)ft_strlen(cub->map.grid[y]) - 1)
		return (0);
	if (y > 0 && x >= (int)ft_strlen(cub->map.grid[y - 1]))
		return (0);
	if (y < cub->map.height - 1 && x >= (int)ft_strlen(cub->map.grid[y + 1]))
		return (0);
	if (cub->map.grid[y - 1][x] == ' ' || cub->map.grid[y + 1][x] == ' ')
		return (0);
	if (cub->map.grid[y][x - 1] == ' ' || cub->map.grid[y][x + 1] == ' ')
		return (0);
	return (1);
}

static int	needs_wall_check(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == 'D');
}

void	validate_map(t_cub3d *cub)
{
	int	y;
	int	x;

	y = 0;
	while (y < cub->map.height)
	{
		x = 0;
		while (cub->map.grid[y][x])
		{
			if (!is_valid_char_bonus(cub->map.grid[y][x]))
				err_exit(cub, ERR_MAP_CHAR);
			if (needs_wall_check(cub->map.grid[y][x])
				&& !check_surrounded(cub, y, x))
				err_exit(cub, ERR_MAP_CLOSED);
			x++;
		}
		y++;
	}
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
			if (cub->map.grid[y][x] == 'N' || cub->map.grid[y][x] == 'S'
				|| cub->map.grid[y][x] == 'E' || cub->map.grid[y][x] == 'W')
			{
				if (cub->parse.player_count > 0)
					err_exit(cub, ERR_MAP_PLAYER);
				cub->parse.player_dir = cub->map.grid[y][x];
				cub->parse.player_x = x;
				cub->parse.player_y = y;
				cub->parse.player_count++;
				cub->map.grid[y][x] = '0';
			}
		}
	}
	if (cub->parse.player_count == 0)
		err_exit(cub, ERR_MAP_PLAYER);
}
