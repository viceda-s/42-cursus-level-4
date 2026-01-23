/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:10:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 11:10:38 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	calculate_tex_x(t_cub3d *cub, t_ray *ray)
{
	t_tex	*tex;

	if (ray->side == 0)
		ray->wall_x = cub->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = cub->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	tex = get_texture(cub, ray);
	ray->tex_x = (int)(ray->wall_x * (double)tex->width);
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_x = tex->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->tex_x = tex->width - ray->tex_x - 1;
}

static int	clamp_tex_coord(int val, int max)
{
	if (val < 0)
		return (0);
	if (val >= max)
		return (max - 1);
	return (val);
}

int	get_texture_color(t_tex *tex, int tex_x, int tex_y)
{
	char	*pixel;

	if (!tex || !tex->addr)
		return (0);
	tex_x = clamp_tex_coord(tex_x, tex->width);
	tex_y = clamp_tex_coord(tex_y, tex->height);
	pixel = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	return (*(int *)pixel);
}
