/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 20:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/06 11:02:09 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	normalize_uv(float *u, float *v)
{
	*u = *u - floorf(*u);
	*v = *v - floorf(*v);
	if (*u < 0)
		*u += 1.0f;
	if (*v < 0)
		*v += 1.0f;
}

static void	clamp_coords(int *x, int *y, t_texture *tex)
{
	if (*x < 0)
		*x = 0;
	if (*x >= tex->width)
		*x = tex->width - 1;
	if (*y < 0)
		*y = 0;
	if (*y >= tex->height)
		*y = tex->height - 1;
}

static int	get_pixel_color(t_texture *tex, int x, int y)
{
	char	*pixel;

	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(int *)pixel);
}

t_gd	get_texture_color(t_texture *tex, float u, float v)
{
	int		x;
	int		y;
	int		color;

	if (!tex || !tex->addr)
		return ((t_gd){.r = 0, .g = 0, .b = 0});
	normalize_uv(&u, &v);
	x = (int)(u * (tex->width - 1));
	y = (int)(v * (tex->height - 1));
	clamp_coords(&x, &y, tex);
	color = get_pixel_color(tex, x, y);
	return ((t_gd){.r = (color >> 16) & 0xFF, .g = (color >> 8) & 0xFF, \
.b = color & 0xFF});
}

float	get_bump_height(t_texture *bump_map, float u, float v)
{
	int		x;
	int		y;
	int		color;
	int		rgb[3];

	if (!bump_map || !bump_map->addr)
		return (0.5f);
	normalize_uv(&u, &v);
	x = (int)(u * (bump_map->width - 1));
	y = (int)(v * (bump_map->height - 1));
	clamp_coords(&x, &y, bump_map);
	color = get_pixel_color(bump_map, x, y);
	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = color & 0xFF;
	return ((rgb[0] + rgb[1] + rgb[2]) / (3.0f * 255.0f));
}
