/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:30:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/22 15:05:19 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calculate_tex_x(t_cub3d *cub, t_ray *ray)
{
	t_tex	*tex;

	if (ray->side == 0)
		ray->wall_x = cub->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = cub->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	tex = get_texture(cub, ray);
	ray->tex_x = ray->wall_x * tex->width;
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_x = tex->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->tex_x = tex->width - ray->tex_x - 1;
}

t_tex	*get_texture(t_cub3d *cub, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (&cub->tex[TEX_EAST]);
		return (&cub->tex[TEX_WEST]);
	}
	if (ray->dir_y > 0)
		return (&cub->tex[TEX_SOUTH]);
	return (&cub->tex[TEX_NORTH]);
}

int	get_texture_color(t_tex *tex, int tex_x, int tex_y)
{
	char	*pixel;

	if (!tex || !tex->addr)
		return (0);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex->height)
		tex_y = tex->height - 1;
	pixel = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	return (*(int *)pixel);
}
