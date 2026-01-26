/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_targets_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/26 14:00:00 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	get_target_color(t_cub3d *cub, int i)
{
	if (cub->targets[i].state == TARGET_HIT)
		return (MM_TARGET_HIT);
	return (MM_TARGET);
}

static void	draw_target_cross(t_cub3d *cub, int px, int py, int color)
{
	int	radius;

	radius = 0;
	while (radius < 3)
	{
		put_pixel(&cub->img, px + radius, py, color);
		put_pixel(&cub->img, px - radius, py, color);
		put_pixel(&cub->img, px, py + radius, color);
		put_pixel(&cub->img, px, py - radius, color);
		radius++;
	}
}

static int	is_target_visible(int px, int py)
{
	if (px >= MINIMAP_X && px < MINIMAP_X + MINIMAP_SIZE
		&& py >= MINIMAP_Y && py < MINIMAP_Y + MINIMAP_SIZE)
		return (1);
	return (0);
}

void	draw_minimap_targets(t_cub3d *cub)
{
	int	i;
	int	px;
	int	py;
	int	color;

	i = 0;
	while (i < cub->target_count)
	{
		px = MINIMAP_X + (int)((cub->targets[i].pos_x - cub->player.pos_x
					+ MINIMAP_SIZE / MINIMAP_SCALE / 2) * MINIMAP_SCALE);
		py = MINIMAP_Y + (int)((cub->targets[i].pos_y - cub->player.pos_y
					+ MINIMAP_SIZE / MINIMAP_SCALE / 2) * MINIMAP_SCALE);
		if (is_target_visible(px, py))
		{
			color = get_target_color(cub, i);
			draw_target_cross(cub, px, py, color);
		}
		i++;
	}
}
