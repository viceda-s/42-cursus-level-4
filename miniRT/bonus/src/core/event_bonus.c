/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:30:20 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/27 19:58:31 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	render_keys(t_minirt *data, int needs_render)
{
	if (needs_render)
	{
		render_scene(data->scene, data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
		render_help_overlay(data);
	}
}

void	exit_program(t_minirt *data)
{
	if (data)
	{
		if (data->scene)
		{
			cleanup_scene_textures(data->mlx, data->scene);
			cleanup_scene(data->scene);
		}
		if (data->img)
			mlx_destroy_image(data->mlx, data->img);
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		if (data->mlx)
		{
			mlx_destroy_display(data->mlx);
			free(data->mlx);
		}
	}
	exit(0);
}

int	close_window(t_minirt *data)
{
	exit_program(data);
	return (0);
}

void	init_event(t_minirt *data)
{
	if (!data || !data->win)
		return ;
	mlx_hook(data->win, 2, 1L << 0, keypress_handler, data);
	mlx_hook(data->win, 17, 0, close_window, data);
}
