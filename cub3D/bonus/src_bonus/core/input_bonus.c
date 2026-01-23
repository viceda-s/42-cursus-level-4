/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:55:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 14:28:58 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	is_moving(t_cub3d *cub)
{
	return (cub->keys[KEY_W] || cub->keys[KEY_S]
		|| cub->keys[KEY_A] || cub->keys[KEY_D]);
}

static void	process_movement(t_cub3d *cub)
{
	if (cub->keys[KEY_W])
		move_forward(cub);
	if (cub->keys[KEY_S])
		move_backward(cub);
	if (cub->keys[KEY_A])
		strafe_left(cub);
	if (cub->keys[KEY_D])
		strafe_right(cub);
}

static void	process_rotation(t_cub3d *cub)
{
	if (cub->key_left)
		rotate_left(cub);
	if (cub->key_right)
		rotate_right(cub);
}

void	process_input(t_cub3d *cub)
{
	cub->weapon.is_walking = is_moving(cub);
	process_movement(cub);
	process_rotation(cub);
}
