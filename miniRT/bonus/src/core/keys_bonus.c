/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:26:13 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/27 19:50:08 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	render_keys(t_minirt *data, int needs_render)
{
	if (needs_render)
	{
		render_scene(data->scene, data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
}

int	keypress_handler3(int key, t_minirt *data, int needs_render)
{
	if (key == KEY_DOWN)
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
	render_keys(data, needs_render);
	return (0);
}

int	keypress_handler2(int key, t_minirt *data, int needs_render)
{
	if (key == KEY_D)
	{
		moving_camera(&data->scene->camera, MOVE_SPEED, 'r');
		needs_render = 1;
	}
	else if (key == KEY_Q)
	{
		moving_camera(&data->scene->camera, MOVE_SPEED, 'u');
		needs_render = 1;
	}
	else if (key == KEY_E)
	{
		moving_camera(&data->scene->camera, -MOVE_SPEED, 'u');
		needs_render = 1;
	}
	else if (key == KEY_UP)
	{
		rotate_camera(&data->scene->camera, ROTATE_SPEED, 0, 0);
		needs_render = 1;
	}
	else
		return (keypress_handler3(key, data, needs_render));
	render_keys(data, needs_render);
	return (0);
}

int	keypress_handler(int key, t_minirt *data)
{
	int	needs_render;

	needs_render = 0;
	if (key == ESC_KEY)
		exit_program(data);
	if (key == KEY_W)
	{
		moving_camera(&data->scene->camera, MOVE_SPEED, 'f');
		needs_render = 1;
	}
	else if (key == KEY_S)
	{
		moving_camera(&data->scene->camera, -MOVE_SPEED, 'f');
		needs_render = 1;
	}
	else if (key == KEY_A)
	{
		moving_camera(&data->scene->camera, MOVE_SPEED, 'l');
		needs_render = 1;
	}
	else
		return (keypress_handler2(key, data, needs_render));
	render_keys(data, needs_render);
	return (0);
}
