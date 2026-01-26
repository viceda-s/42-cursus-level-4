/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target_mission_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/26 14:00:00 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	draw_message_background(t_cub3d *cub, t_rect rect)
{
	int	i;
	int	j;

	i = 0;
	while (i < rect.height)
	{
		j = 0;
		while (j < rect.width)
		{
			put_pixel(&cub->img, rect.x + j, rect.y + i, 0x000000);
			j++;
		}
		i++;
	}
}

void	draw_mission_complete(t_cub3d *cub)
{
	t_rect	rect;

	rect.x = WIN_WIDTH / 2 - 125;
	rect.y = WIN_HEIGHT / 2 - 200;
	rect.width = 250;
	rect.height = 60;
	draw_message_background(cub, rect);
	mlx_string_put(cub->mlx, cub->win, WIN_WIDTH / 2 - 75,
		WIN_HEIGHT / 2 - 180, 0xFF0000, "*** ALL TARGETS CLEARED ***");
	mlx_string_put(cub->mlx, cub->win, WIN_WIDTH / 2 - 45,
		WIN_HEIGHT / 2 - 160, 0xFFAA00, "MISSION COMPLETE!");
}
