/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_control_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 00:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/03 14:27:48 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	keypress_handler_lights(int key, t_minirt *data)
{
	t_vector	offset;
	int			needs_render;
	t_l			*l;

	l = (t_l *)data->scene->lights_list->content;
	offset = (t_vector){0, 0, 0};
	needs_render = 0;
	if (key == KEY_L)
		offset.x = 10.0f;
	else if (key == KEY_J)
		offset.x = -10.0f;
	else if (key == KEY_I)
		offset.z = 10.0f;
	else if (key == KEY_K)
		offset.z = -10.0f;
	else if (key == KEY_U)
		offset.y = 10.0f;
	else if (key == KEY_O)
		offset.y = -10.0f;
	if (offset.x != 0 || offset.y != 0 || offset.z != 0)
	{
		translate_light(l, offset);
		needs_render = 1;
	}
	return (needs_render);
}
