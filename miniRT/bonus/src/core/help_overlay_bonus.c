/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_overlay_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 00:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/06 00:00:00 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	draw_text(t_minirt *d, int y, char *text, int color)
{
	mlx_string_put(d->mlx, d->win, 10, y, color, text);
}

static void	draw_camera_controls(t_minirt *data, int *y)
{
	draw_text(data, *y, "CAMERA:", 0xFFFF00);
	*y += 20;
	draw_text(data, *y, "  A/D - Move X axis", 0xFFFFFF);
	*y += 15;
	draw_text(data, *y, "  W/S - Move Y axis", 0xFFFFFF);
	*y += 15;
	draw_text(data, *y, "  Z/E - Move Z axis", 0xFFFFFF);
	*y += 15;
	draw_text(data, *y, "  Arrows - Rotate camera", 0xFFFFFF);
	*y += 20;
	draw_text(data, *y, "RENDER:", 0xFFFF00);
	*y += 20;
	draw_text(data, *y, "  F - Toggle AA", 0xFFFFFF);
	*y += 15;
	draw_text(data, *y, "  H - Toggle help", 0xFFFFFF);
	*y += 5;
}

static void	draw_light_object_controls(t_minirt *data, int *y)
{
	draw_text(data, *y, "LIGHTS:", 0xFFFF00);
	*y += 20;
	draw_text(data, *y, "  J/L - Move X axis", 0xFFFFFF);
	*y += 15;
	draw_text(data, *y, "  U/O - Move Y axis", 0xFFFFFF);
	*y += 15;
	draw_text(data, *y, "  I/K - Move Z axis", 0xFFFFFF);
	*y += 20;
	draw_text(data, *y, "OBJECTS:", 0xFFFF00);
	*y += 20;
	draw_text(data, *y, "  TAB - Select", 0xFFFFFF);
	*y += 15;
	draw_text(data, *y, "  Numpad 4/6 - Move X axis", 0xFFFFFF);
	*y += 15;
	draw_text(data, *y, "  Numpad 2/8 - Move Y axis", 0xFFFFFF);
	*y += 15;
	draw_text(data, *y, "  Numpad 1/9 - Move Z axis", 0xFFFFFF);
	*y += 5;
}

void	render_help_overlay(t_minirt *data)
{
	int	y;

	if (!data->show_help)
		return ;
	y = 30;
	draw_text(data, y, "=== CONTROLS ===", 0x00FF00);
	y += 25;
	draw_camera_controls(data, &y);
	y += 15;
	draw_light_object_controls(data, &y);
	y += 15;
	draw_text(data, y, "ESC - Exit", 0xFF0000);
}
