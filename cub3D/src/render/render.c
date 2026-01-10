/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:30:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/12/02 15:58:31 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	game_loop(t_cub3d *cub)
{
	process_input(cub);
	draw_floor_ceiling(cub);
	raycast(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	return (0);
}
