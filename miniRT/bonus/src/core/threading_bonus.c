/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 00:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/03 16:12:06 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	render_row(t_minirt *data, t_viewport viewport, int y)
{
	t_gd	color;
	int		x;

	x = 0;
	while (x < viewport.width)
	{
		color = get_pixel_color_aa_quality((t_aa_params){data->scene,
				x, y, viewport}, ANTI_ALIASING_SAMPLES);
		put_pixel(data, x, y, color_to_int(color));
		x++;
	}
}

void	*render_slice(void *arg)
{
	t_thread_data	*thread_data;
	t_minirt		*data;
	t_viewport		viewport;
	int				y;

	thread_data = (t_thread_data *)arg;
	data = thread_data->data;
	viewport.width = data->win_width;
	viewport.height = data->win_height;
	viewport.aspect_ratio = (float)data->win_width / (float)data->win_height;
	y = thread_data->start_y;
	while (y < thread_data->end_y)
	{
		render_row(data, viewport, y);
		y++;
	}
	return (NULL);
}
