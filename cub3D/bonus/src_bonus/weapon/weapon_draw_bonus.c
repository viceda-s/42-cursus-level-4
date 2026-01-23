/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_draw_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:30:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 14:35:54 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	is_transparent(int color)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	if (r >= 240 && b >= 240 && g <= 30)
		return (1);
	if ((color & 0x00FFFFFF) == 0)
		return (1);
	if ((color & 0x00FFFFFF) == 0xFF00FF)
		return (1);
	return (0);
}

static void	draw_weapon_row(t_cub3d *cub, t_tex *tex, int *pos, int y)
{
	int	x;
	int	color;

	x = 0;
	while (x < tex->width)
	{
		color = get_texture_color(tex, x, y);
		if (!is_transparent(color))
			put_pixel(&cub->img, pos[0] + x, pos[1] + y, color);
		x++;
	}
}

void	draw_weapon(t_cub3d *cub)
{
	int		y;
	int		pos[2];
	t_tex	*current;

	current = &cub->weapon.sprites[cub->weapon.current_frame];
	if (!current->img)
		return ;
	pos[0] = (WIN_WIDTH - current->width) / 2 + cub->weapon.bob_x;
	pos[1] = WIN_HEIGHT - current->height + cub->weapon.bob_y;
	y = 0;
	while (y < current->height)
	{
		draw_weapon_row(cub, current, pos, y);
		y++;
	}
}
