/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:30:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/12/02 16:33:13 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	draw_minimap_background(t_cub3d *cub)
{
	int	x;
	int	y;

	y = MINIMAP_Y;
	while (y < MINIMAP_Y + MINIMAP_SIZE)
	{
		x = MINIMAP_X;
		while (x < MINIMAP_X + MINIMAP_SIZE)
		{
			put_pixel(&cub->img, x, y, MM_BG);
			x++;
		}
		y++;
	}
}

static int	get_tile_color(t_cub3d *cub, int mx, int my)
{
	char	tile;

	if (mx < 0 || my < 0 || my >= cub->map.height || mx >= cub->map.width)
		return (MM_BG);
	if (!cub->map.grid[my] || mx >= (int)ft_strlen(cub->map.grid[my]))
		return (MM_BG);
	tile = cub->map.grid[my][mx];
	if (tile == '1')
		return (MM_WALL);
	if (tile == 'D')
	{
		if (is_door_open(cub, mx, my))
			return (MM_DOOR_OPEN);
		return (MM_DOOR);
	}
	if (tile == '0' || tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
		return (MM_FLOOR);
	return (MM_BG);
}

static void	draw_minimap_tiles(t_cub3d *cub)
{
	int		px;
	int		py;
	int		mx;
	int		my;
	int		color;

	py = 0;
	while (py < MINIMAP_SIZE)
	{
		px = 0;
		while (px < MINIMAP_SIZE)
		{
			mx = (int)(cub->player.pos_x - MINIMAP_SIZE / MINIMAP_SCALE / 2)
				+ px / MINIMAP_SCALE;
			my = (int)(cub->player.pos_y - MINIMAP_SIZE / MINIMAP_SCALE / 2)
				+ py / MINIMAP_SCALE;
			color = get_tile_color(cub, mx, my);
			put_pixel(&cub->img, MINIMAP_X + px, MINIMAP_Y + py, color);
			px++;
		}
		py++;
	}
}

static void	draw_player_marker(t_cub3d *cub)
{
	int		cx;
	int		cy;
	int		i;
	int		dx;
	int		dy;

	cx = MINIMAP_X + MINIMAP_SIZE / 2;
	cy = MINIMAP_Y + MINIMAP_SIZE / 2;
	put_pixel(&cub->img, cx, cy, MM_PLAYER);
	put_pixel(&cub->img, cx + 1, cy, MM_PLAYER);
	put_pixel(&cub->img, cx - 1, cy, MM_PLAYER);
	put_pixel(&cub->img, cx, cy + 1, MM_PLAYER);
	put_pixel(&cub->img, cx, cy - 1, MM_PLAYER);
	i = 0;
	while (i < 8)
	{
		dx = (int)(cub->player.dir_x * i);
		dy = (int)(cub->player.dir_y * i);
		put_pixel(&cub->img, cx + dx, cy + dy, MM_PLAYER);
		i++;
	}
}

void	draw_minimap(t_cub3d *cub)
{
	draw_minimap_background(cub);
	draw_minimap_tiles(cub);
	draw_player_marker(cub);
}