/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:15:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 12:35:04 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	game_loop(t_cub3d *cub)
{
	process_input(cub);
	update_doors(cub);
	update_weapon(cub);
	draw_floor_ceiling(cub);
	raycast(cub);
	render_sprites(cub, cub->z_buffer);
	draw_minimap(cub);
	draw_weapon(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	draw_score(cub);
	return (0);
}
