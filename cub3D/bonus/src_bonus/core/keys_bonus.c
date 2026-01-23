/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:55:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 11:12:28 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	handle_special_keys(int keycode, t_cub3d *cub)
{
	if (keycode == KEY_E)
		toggle_door(cub);
}

int	key_press(int keycode, t_cub3d *cub)
{
	if (keycode == KEY_ESC)
		close_window(cub);
	handle_special_keys(keycode, cub);
	if (keycode == KEY_LEFT)
		cub->key_left = 1;
	else if (keycode == KEY_RIGHT)
		cub->key_right = 1;
	else if (keycode >= 0 && keycode < 256)
		cub->keys[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_cub3d *cub)
{
	if (keycode == KEY_LEFT)
		cub->key_left = 0;
	else if (keycode == KEY_RIGHT)
		cub->key_right = 0;
	else if (keycode >= 0 && keycode < 256)
		cub->keys[keycode] = 0;
	return (0);
}
