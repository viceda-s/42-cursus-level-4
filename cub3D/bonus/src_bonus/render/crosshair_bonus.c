/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/26 13:00:00 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	draw_crosshair_vertical(t_cub3d *cub, int cx, int cy);

static void	draw_line_pixel(t_cub3d *cub, t_line line, t_line_data data)
{
	int	thick;

	thick = 0;
	while (thick < CROSSHAIR_THICK)
	{
		if (data.dx > data.dy)
			put_pixel(&cub->img, line.start_x + data.t,
				line.start_y + thick, CROSSHAIR_COLOR);
		else
			put_pixel(&cub->img, line.start_x + thick,
				line.start_y + data.t, CROSSHAIR_COLOR);
		thick++;
	}
}

static void	draw_crosshair_line(t_cub3d *cub, t_line line)
{
	t_line_data	data;
	int			max;

	data.dx = line.end_x - line.start_x;
	data.dy = line.end_y - line.start_y;
	if (data.dx > data.dy)
		max = data.dx;
	else
		max = data.dy;
	data.t = 0;
	while (data.t <= max)
	{
		draw_line_pixel(cub, line, data);
		data.t++;
	}
}

void	draw_crosshair(t_cub3d *cub)
{
	int		cx;
	int		cy;
	t_line	line;

	cx = WIN_WIDTH / 2;
	cy = WIN_HEIGHT / 2;
	line.start_x = cx - CROSSHAIR_SIZE;
	line.start_y = cy;
	line.end_x = cx - CROSSHAIR_GAP;
	line.end_y = cy;
	draw_crosshair_line(cub, line);
	line.start_x = cx + CROSSHAIR_GAP;
	line.end_x = cx + CROSSHAIR_SIZE;
	draw_crosshair_line(cub, line);
	draw_crosshair_vertical(cub, cx, cy);
	put_pixel(&cub->img, cx, cy, CROSSHAIR_COLOR);
}

static void	draw_crosshair_vertical(t_cub3d *cub, int cx, int cy)
{
	t_line	line;

	line.start_x = cx;
	line.start_y = cy - CROSSHAIR_SIZE;
	line.end_x = cx;
	line.end_y = cy - CROSSHAIR_GAP;
	draw_crosshair_line(cub, line);
	line.start_y = cy + CROSSHAIR_GAP;
	line.end_y = cy + CROSSHAIR_SIZE;
	draw_crosshair_line(cub, line);
}
