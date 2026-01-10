/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg.>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:22:51 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/04 13:22:52 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 00:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/27 19:53:42 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	moving_camera(t_camera *camera, float distance, char flag)
{
	t_vector	movement;

	movement = (t_vector){0, 0, 0};
	if (flag == 'f')
		movement = vector_scale(camera->forward, distance);
	else if (flag == 'r')
		movement = vector_scale(camera->right, distance);
	else if (flag == 'l')
		movement = vector_scale(camera->right, -distance);
	else if (flag == 'u')
		movement = vector_scale(camera->up, distance);
	camera->position = vector_add(camera->position, movement);
}

void	update_camera_vectors(t_camera *camera)
{
	camera->right = vector_normalize(vector_cross(camera->forward, camera->up));
	camera->up = vector_normalize(vector_cross(camera->right, camera->forward));
}

t_vector	rotate_axis(t_vector v, float angle, int axis)
{
	float		cos_a;
	float		sin_a;
	t_vector	result;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	if (axis == 0)
	{
		result.x = v.x;
		result.y = v.y * cos_a - v.z * sin_a;
		result.z = v.y * sin_a + v.z * cos_a;
	}
	else if (axis == 1)
	{
		result.x = v.x * cos_a + v.z * sin_a;
		result.y = v.y;
		result.z = -v.x * sin_a + v.z * cos_a;
	}
	else
	{
		result.x = v.x * cos_a - v.y * sin_a;
		result.y = v.x * sin_a + v.y * cos_a;
		result.z = v.z;
	}
	return (result);
}

void	rotate_camera(t_camera *camera, float pitch, float yaw, float roll)
{
	if (pitch != 0)
		camera->forward = rotate_axis(camera->forward, pitch, 0);
	if (yaw != 0)
		camera->forward = rotate_axis(camera->forward, yaw, 1);
	if (roll != 0)
		camera->forward = rotate_axis(camera->forward, roll, 2);
	update_camera_vectors(camera);
}

void	move_camera(t_camera *camera, t_vector direction, float distance)
{
	camera->position = vector_add(camera->position,
			vector_scale(vector_normalize(direction), distance));
}
