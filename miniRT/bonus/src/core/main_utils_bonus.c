/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:30:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/05 21:58:44 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt_bonus.h"

int	init_minirt(t_minirt *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->win_width = 1280;
	data->win_height = 720;
	data->win = mlx_new_window(data->mlx, data->win_width,
			data->win_height, "miniRT");
	if (!data->win)
		return (1);
	data->img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	if (!data->img)
		return (1);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	if (!data->addr)
		return (1);
	return (0);
}

void	put_pixel(t_minirt *data, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < data->win_width && y >= 0 && y < data->win_height)
	{
		pixel = data->addr + (y * data->line_length
				+ x * (data->bits_per_pixel / 8));
		*(int *)pixel = color;
	}
}
