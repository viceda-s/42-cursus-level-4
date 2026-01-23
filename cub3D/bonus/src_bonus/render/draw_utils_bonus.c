/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:15:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 11:12:30 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	calc_wall_params(t_ray *ray, double perp_dist, int *params)
{
	params[0] = (int)(WIN_HEIGHT / perp_dist);
	params[1] = -params[0] / 2 + WIN_HEIGHT / 2;
	if (params[1] < 0)
		params[1] = 0;
	params[2] = params[0] / 2 + WIN_HEIGHT / 2;
	if (params[2] >= WIN_HEIGHT)
		params[2] = WIN_HEIGHT - 1;
	(void)ray;
}

double	calc_wall_x(t_cub3d *cub, t_ray *ray, double perp_dist)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = cub->player.pos_y + perp_dist * ray->dir_y;
	else
		wall_x = cub->player.pos_x + perp_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	calc_tex_x(t_cub3d *cub, t_ray *ray, t_tex *tex, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)tex->width);
	if (ray->side == 0 && ray->dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	(void)cub;
	return (tex_x);
}

void	draw_tex_column(t_cub3d *cub, t_tex *tex, int *p, int x)
{
	int		y;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;

	step = 1.0 * tex->height / p[0];
	tex_pos = (p[1] - WIN_HEIGHT / 2 + p[0] / 2) * step;
	y = p[1];
	while (y < p[2])
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		color = get_texture_color(tex, p[3], tex_y);
		if (p[4] || (color & 0xFFFFFF) != TRANSPARENT_COLOR)
			put_pixel(&cub->img, x, y, color);
		y++;
	}
}
