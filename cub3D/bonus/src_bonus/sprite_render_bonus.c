/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 00:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 12:37:35 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	init_sprite_transform(t_cub3d *cub, t_sprite *sprite,
								double *transform, double *sprite_rel)
{
	double	inv_det;

	sprite_rel[0] = sprite->x - cub->player.pos_x;
	sprite_rel[1] = sprite->y - cub->player.pos_y;
	inv_det = 1.0 / (cub->player.plane_x * cub->player.dir_y
			- cub->player.dir_x * cub->player.plane_y);
	transform[0] = inv_det * (cub->player.dir_y * sprite_rel[0]
			- cub->player.dir_x * sprite_rel[1]);
	transform[1] = inv_det * (-cub->player.plane_y * sprite_rel[0]
			+ cub->player.plane_x * sprite_rel[1]);
}

static void	calc_sprite_screen_props(double transform_y, int *props)
{
	props[0] = (int)((WIN_WIDTH / 2) * (1 + props[4] / transform_y));
	props[1] = abs((int)(WIN_HEIGHT / transform_y));
	props[2] = abs((int)(WIN_HEIGHT / transform_y));
	props[3] = -props[1] / 2 + WIN_HEIGHT / 2;
	if (props[3] < 0)
		props[3] = 0;
	props[5] = props[1] / 2 + WIN_HEIGHT / 2;
	if (props[5] >= WIN_HEIGHT)
		props[5] = WIN_HEIGHT - 1;
	props[6] = -props[2] / 2 + props[0];
	if (props[6] < 0)
		props[6] = 0;
	props[7] = props[2] / 2 + props[0];
	if (props[7] >= WIN_WIDTH)
		props[7] = WIN_WIDTH - 1;
}

static void	draw_sprite_col(t_cub3d *cub, t_tex *tex, int *p, int stripe)
{
	int		y;
	int		tex_x;
	int		tex_y;
	int		color;
	double	d;

	tex_x = (int)(256 * (stripe - (-p[2] / 2 + p[0]))
			* tex->width / p[2]) / 256;
	y = p[3];
	while (y < p[5])
	{
		d = (y) * 256 - WIN_HEIGHT * 128 + p[1] * 128;
		tex_y = ((d * tex->height) / p[1]) / 256;
		if (tex_y >= 0 && tex_y < tex->height)
		{
			color = get_texture_color(tex, tex_x, tex_y);
			if (color != TRANSPARENT_COLOR && (color & 0x00FFFFFF) != 0)
				put_pixel(&cub->img, stripe, y, color);
		}
		y++;
	}
}

static void	draw_sprite_stripes(t_cub3d *cub, t_tex *tex, int *p, double *buf)
{
	int	stripe;

	stripe = p[6];
	while (stripe < p[7])
	{
		if (p[8] > 0 && stripe > 0 && stripe < WIN_WIDTH && p[8] < buf[stripe])
			draw_sprite_col(cub, tex, p, stripe);
		stripe++;
	}
}

void	draw_sprite(t_cub3d *cub, t_sprite *sprite, double *z_buffer)
{
	double	transform[2];
	double	sprite_rel[2];
	int		props[9];
	t_tex	*tex;

	init_sprite_transform(cub, sprite, transform, sprite_rel);
	if (transform[1] <= 0)
		return ;
	props[4] = (int)(transform[0]);
	calc_sprite_screen_props(transform[1], props);
	if (sprite->tex < 0 || sprite->tex >= 2)
		return ;
	tex = &cub->target_tex[sprite->tex];
	if (!tex->img)
		return ;
	props[8] = (int)(transform[1] * 1000) / 1000;
	draw_sprite_stripes(cub, tex, props, z_buffer);
}
