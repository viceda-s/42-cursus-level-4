/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:26:13 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/03 14:51:36 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	toggle_help(t_minirt *data)
{
	data->show_help = !data->show_help;
	if (data->show_help)
		ft_printf("Help overlay: ON\n");
	else
		ft_printf("Help overlay: OFF\n");
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
		rotate_camera(&data->scene->camera, 0, ROTATE_SPEED, 0);
		needs_render = 1;
	}
	else if (key == KEY_RIGHT)
	{
		rotate_camera(&data->scene->camera, 0, -ROTATE_SPEED, 0);
		needs_render = 1;
	}
	else
	{
		needs_render |= keypress_handler_lights(key, data);
		needs_render |= keypress_handler_objects(key, data);
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
	else if (key == KEY_Z)
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

static int	handle_movement_keys(int key, t_minirt *data)
{
	if (key == KEY_W)
		moving_camera(&data->scene->camera, MOVE_SPEED, 'f');
	else if (key == KEY_S)
		moving_camera(&data->scene->camera, -MOVE_SPEED, 'f');
	else if (key == KEY_A)
		moving_camera(&data->scene->camera, MOVE_SPEED, 'l');
	else
		return (0);
	return (1);
}

int	keypress_handler(int key, t_minirt *data)
{
	int	needs_render;

	needs_render = 0;
	if (key == ESC_KEY)
		exit_program(data);
	if (key == KEY_F)
	{
		data->fast_render = !data->fast_render;
		if (data->fast_render)
			ft_printf("Fast render (AA off): ON\n");
		else
			ft_printf("Fast render (AA off): OFF\n");
		needs_render = 1;
	}
	else if (key == KEY_H)
	{
		toggle_help(data);
		needs_render = 1;
	}
	else if (handle_movement_keys(key, data))
		needs_render = 1;
	else
		return (keypress_handler2(key, data, needs_render));
	render_keys(data, needs_render);
	return (0);
}
