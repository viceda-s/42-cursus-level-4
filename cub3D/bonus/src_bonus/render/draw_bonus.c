/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:15:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 11:12:26 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	put_pixel(t_tex *img, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(int *)pixel = color;
	}
}

void	draw_floor_ceiling(t_cub3d *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(&cub->img, x, y, cub->ceiling_color);
			x++;
		}
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(&cub->img, x, y, cub->floor_color);
			x++;
		}
		y++;
	}
}

static double	get_perp_dist(t_cub3d *cub, t_ray *ray, int bg)
{
	if (bg && ray->has_wall_behind)
	{
		ray->map_x = ray->wall_map_x;
		ray->map_y = ray->wall_map_y;
		ray->side = ray->wall_side;
		return (ray->wall_perp_dist);
	}
	else if (!bg && ray->hit_door)
	{
		ray->map_x = ray->door_map_x;
		ray->map_y = ray->door_map_y;
		ray->side = ray->door_side;
		return (ray->door_perp_dist);
	}
	(void)cub;
	return (ray->perp_wall_dist);
}

static void	draw_wall_column(t_cub3d *cub, t_ray *ray, int x, int bg)
{
	int		saved[3];
	int		p[5];
	double	perp_dist;
	t_tex	*tex;

	saved[0] = ray->map_x;
	saved[1] = ray->map_y;
	saved[2] = ray->side;
	perp_dist = get_perp_dist(cub, ray, bg);
	if (perp_dist < 0.0001)
		perp_dist = 0.0001;
	calc_wall_params(ray, perp_dist, p);
	tex = get_texture(cub, ray);
	p[3] = calc_tex_x(cub, ray, tex, calc_wall_x(cub, ray, perp_dist));
	p[4] = bg;
	draw_tex_column(cub, tex, p, x);
	ray->map_x = saved[0];
	ray->map_y = saved[1];
	ray->side = saved[2];
}

void	draw_column(t_cub3d *cub, t_ray *ray, int x)
{
	if (ray->hit_door && ray->has_wall_behind)
	{
		draw_wall_column(cub, ray, x, 1);
		draw_wall_column(cub, ray, x, 0);
	}
	else
		draw_wall_column(cub, ray, x, 0);
}
