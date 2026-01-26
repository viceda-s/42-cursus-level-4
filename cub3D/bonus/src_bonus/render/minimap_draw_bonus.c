/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/26 14:00:00 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	draw_player_direction(t_cub3d *cub, int cx, int cy)
{
	int	i;
	int	dx;
	int	dy;

	i = 0;
	while (i < 10)
	{
		dx = (int)(cub->player.dir_x * i);
		dy = (int)(cub->player.dir_y * i);
		put_pixel(&cub->img, cx + dx, cy + dy, MM_PLAYER);
		i++;
	}
}

static void	draw_player_wings(t_cub3d *cub, int cx, int cy)
{
	int	i;
	int	dx;
	int	dy;
	int	perp_x;
	int	perp_y;

	i = 3;
	while (i <= 5)
	{
		perp_x = (int)(-cub->player.dir_y * i);
		perp_y = (int)(cub->player.dir_x * i);
		put_pixel(&cub->img, cx + perp_x, cy + perp_y, MM_PLAYER);
		put_pixel(&cub->img, cx - perp_x, cy - perp_y, MM_PLAYER);
		dx = (int)(cub->player.dir_x * (i - 5));
		dy = (int)(cub->player.dir_y * (i - 5));
		put_pixel(&cub->img, cx + dx + perp_x, cy + dy + perp_y, MM_PLAYER);
		put_pixel(&cub->img, cx + dx - perp_x, cy + dy - perp_y, MM_PLAYER);
		i++;
	}
}

void	draw_player_marker(t_cub3d *cub)
{
	int	cx;
	int	cy;

	cx = MINIMAP_X + MINIMAP_SIZE / 2;
	cy = MINIMAP_Y + MINIMAP_SIZE / 2;
	draw_player_direction(cub, cx, cy);
	draw_player_wings(cub, cx, cy);
}

void	draw_minimap_border(t_cub3d *cub)
{
	int	x;
	int	y;
	int	thickness;

	thickness = 0;
	while (thickness < 2)
	{
		x = MINIMAP_X + thickness;
		while (x < MINIMAP_X + MINIMAP_SIZE - thickness)
		{
			put_pixel(&cub->img, x, MINIMAP_Y + thickness, MM_BORDER);
			put_pixel(&cub->img, x, MINIMAP_Y + MINIMAP_SIZE - 1 - thickness,
				MM_BORDER);
			x++;
		}
		y = MINIMAP_Y + thickness;
		while (y < MINIMAP_Y + MINIMAP_SIZE - thickness)
		{
			put_pixel(&cub->img, MINIMAP_X + thickness, y, MM_BORDER);
			put_pixel(&cub->img, MINIMAP_X + MINIMAP_SIZE - 1 - thickness, y,
				MM_BORDER);
			y++;
		}
		thickness++;
	}
}
