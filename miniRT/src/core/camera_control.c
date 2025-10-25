/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 00:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/25 00:00:00 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Rotate vector around X axis
t_vector	rotate_x(t_vector v, float angle)
{
	t_vector	result;
	float		cos_a;
	float		sin_a;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	result.x = v.x;
	result.y = v.y * cos_a - v.z * sin_a;
	result.z = v.y * sin_a + v.z * cos_a;
	return (result);
}

// Rotate vector around Y axis
t_vector	rotate_y(t_vector v, float angle)
{
	t_vector	result;
	float		cos_a;
	float		sin_a;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	result.x = v.x * cos_a + v.z * sin_a;
	result.y = v.y;
	result.z = -v.x * sin_a + v.z * cos_a;
	return (result);
}

// Rotate vector around Z axis
t_vector	rotate_z(t_vector v, float angle)
{
	t_vector	result;
	float		cos_a;
	float		sin_a;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	result.x = v.x * cos_a - v.y * sin_a;
	result.y = v.x * sin_a + v.y * cos_a;
	result.z = v.z;
	return (result);
}

// Update camera orientation vectors after rotation
void	update_camera_vectors(t_camera *camera)
{
	t_vector	world_up;

	world_up = vector_create(0, 1, 0);
	camera->forward = vector_normalize(camera->forward);
	
	// If forward is parallel to world_up, use different reference
	if (fabsf(vector_dot(camera->forward, world_up)) > 0.999f)
		world_up = vector_create(0, 0, 1);
	
	camera->right = vector_normalize(vector_cross(camera->forward, world_up));
	camera->up = vector_normalize(vector_cross(camera->right, camera->forward));
}

// Rotate camera (pitch = X, yaw = Y, roll = Z)
void	rotate_camera(t_camera *camera, float pitch, float yaw, float roll)
{
	if (pitch != 0.0f)
		camera->forward = rotate_x(camera->forward, pitch);
	if (yaw != 0.0f)
		camera->forward = rotate_y(camera->forward, yaw);
	if (roll != 0.0f)
		camera->forward = rotate_z(camera->forward, roll);
	
	update_camera_vectors(camera);
}

// Move camera in a direction
void	move_camera(t_camera *camera, t_vector direction, float distance)
{
	t_vector	movement;

	movement = vector_scale(direction, distance);
	camera->position = vector_add(camera->position, movement);
}

// Move camera forward/backward
void	camera_move_forward(t_camera *camera, float distance)
{
	move_camera(camera, camera->forward, distance);
}

// Move camera left/right
void	camera_move_right(t_camera *camera, float distance)
{
	move_camera(camera, camera->right, distance);
}

// Move camera up/down
void	camera_move_up(t_camera *camera, float distance)
{
	move_camera(camera, camera->up, distance);
}
