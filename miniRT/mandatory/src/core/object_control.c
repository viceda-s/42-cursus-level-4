/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg.>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:22:36 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/04 13:22:36 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_control_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 00:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/03 14:36:19 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	handle_translation(int key, t_objects *obj)
{
	t_vector	offset;

	offset = (t_vector){0, 0, 0};
	if (key == KEY_PAD_6)
		offset.x = 1.0f;
	else if (key == KEY_PAD_4)
		offset.x = -1.0f;
	else if (key == KEY_PAD_8)
		offset.y = 1.0f;
	else if (key == KEY_PAD_2)
		offset.y = -1.0f;
	else if (key == KEY_PAD_9)
		offset.z = 1.0f;
	else if (key == KEY_PAD_7)
		offset.z = -1.0f;
	if (offset.x != 0 || offset.y != 0 || offset.z != 0)
		translate_object(obj->object_data, obj->type, offset);
}

static void	handle_rotation(int key, t_objects *obj)
{
	t_rotation	rot;

	rot.pitch = 0;
	rot.yaw = 0;
	rot.roll = 0;
	if (key == KEY_PAD_UP)
		rot.pitch = ROTATE_SPEED;
	else if (key == KEY_PAD_DOWN)
		rot.pitch = -ROTATE_SPEED;
	else if (key == KEY_PAD_LEFT)
		rot.yaw = ROTATE_SPEED;
	else if (key == KEY_PAD_RIGHT)
		rot.yaw = -ROTATE_SPEED;
	if (rot.pitch != 0 || rot.yaw != 0 || rot.roll != 0)
		rotate_object(obj->object_data, obj->type, rot);
}

int	keypress_handler_objects(int key, t_minirt *data)
{
	int	needs_render;

	needs_render = 0;
	if (key == KEY_TAB)
	{
		select_next_object(data->scene);
		printf("Selected object changed.\n");
		needs_render = 1;
	}
	if (data->scene->selected_object)
	{
		handle_translation(key, data->scene->selected_object);
		handle_rotation(key, data->scene->selected_object);
		needs_render = 1;
	}
	return (needs_render);
}
