/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:30:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 16:43:47 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_window(t_cub3d *cub)
{
	cleanup(cub);
	exit(0);
	return (0);
}

void	setup_hooks(t_cub3d *cub)
{
	if (!cub || !cub->win)
		return ;
	mlx_hook(cub->win, X_EVENT_KEY_PRESS, 1L << 0, key_press, cub);
	mlx_hook(cub->win, X_EVENT_KEY_RELEASE, 1L << 1, key_release, cub);
	mlx_hook(cub->win, X_EVENT_DESTROY, 0, close_window, cub);
	mlx_loop_hook(cub->mlx, game_loop, cub);
}
