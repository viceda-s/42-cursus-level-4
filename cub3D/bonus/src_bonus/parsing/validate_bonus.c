/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 13:04:46 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	is_valid_char_bonus(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'D');
}

static int	is_target_char(char c)
{
	return (c == 'T');
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
		|| c == 'D' || c == 'T');
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
			if (!is_valid_char_bonus(cub->map.grid[y][x])
				&& !is_target_char(cub->map.grid[y][x]))
				err_exit(cub, ERR_MAP_CHAR);
			if (needs_wall_check(cub->map.grid[y][x])
				&& !check_surrounded(cub, y, x))
				err_exit(cub, ERR_MAP_CLOSED);
			x++;
		}
		y++;
	}
}
