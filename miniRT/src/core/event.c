/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:30:20 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/10 17:10:05 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	exit_program(t_minirt *data)
{
	if (data)
	{
		if(data->img)
			mlx_destroy_image(data->mlx, data->img);
		if(data->win)
			mlx_destroy_window(data->mlx, data->win);
		if(data->mlx)
		{
			mlx_destroy_display(data->mlx);
			free(data->mlx);
		}
		if (data->scene)
			cleanup_scene(data->scene);
	}
	exit(0);
	return (0);
}

int	keypress_handler(int key, t_minirt *data)
{
	int	needs_render;

	needs_render = 0;
	if (key == ESC_KEY)
		exit_program(data);
	
	// Movement keys (WASD + QE for up/down)
	if (key == KEY_W)
	{
		camera_move_forward(&data->scene->camera, MOVE_SPEED);
		needs_render = 1;
	}
	else if (key == KEY_S)
	{
		camera_move_forward(&data->scene->camera, -MOVE_SPEED);
		needs_render = 1;
	}
	else if (key == KEY_A)
	{
		camera_move_right(&data->scene->camera, -MOVE_SPEED);
		needs_render = 1;
	}
	else if (key == KEY_D)
	{
		camera_move_right(&data->scene->camera, MOVE_SPEED);
		needs_render = 1;
	}
	else if (key == KEY_Q)
	{
		camera_move_up(&data->scene->camera, MOVE_SPEED);
		needs_render = 1;
	}
	else if (key == KEY_E)
	{
		camera_move_up(&data->scene->camera, -MOVE_SPEED);
		needs_render = 1;
	}
	
	// Rotation keys (Arrow keys)
	else if (key == KEY_UP)
	{
		rotate_camera(&data->scene->camera, ROTATE_SPEED, 0, 0);
		needs_render = 1;
	}
	else if (key == KEY_DOWN)
	{
		rotate_camera(&data->scene->camera, -ROTATE_SPEED, 0, 0);
		needs_render = 1;
	}
	else if (key == KEY_LEFT)
	{
		rotate_camera(&data->scene->camera, 0, -ROTATE_SPEED, 0);
		needs_render = 1;
	}
	else if (key == KEY_RIGHT)
	{
		rotate_camera(&data->scene->camera, 0, ROTATE_SPEED, 0);
		needs_render = 1;
	}
	
	// Re-render if camera moved
	if (needs_render)
	{
		render_scene(data->scene, data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	
	return (0);
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
