/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:05:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/12/02 16:33:13 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	move_forward(t_cub3d *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.pos_x + cub->player.dir_x * cub->player.move_speed;
	new_y = cub->player.pos_y + cub->player.dir_y * cub->player.move_speed;
	if (!is_wall_bonus(cub, new_x, cub->player.pos_y))
		cub->player.pos_x = new_x;
	if (!is_wall_bonus(cub, cub->player.pos_x, new_y))
		cub->player.pos_y = new_y;
}

void	move_backward(t_cub3d *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.pos_x - cub->player.dir_x * cub->player.move_speed;
	new_y = cub->player.pos_y - cub->player.dir_y * cub->player.move_speed;
	if (!is_wall_bonus(cub, new_x, cub->player.pos_y))
		cub->player.pos_x = new_x;
	if (!is_wall_bonus(cub, cub->player.pos_x, new_y))
		cub->player.pos_y = new_y;
}

void	strafe_left(t_cub3d *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.pos_x - cub->player.plane_x * cub->player.move_speed;
	new_y = cub->player.pos_y - cub->player.plane_y * cub->player.move_speed;
	if (!is_wall_bonus(cub, new_x, cub->player.pos_y))
		cub->player.pos_x = new_x;
	if (!is_wall_bonus(cub, cub->player.pos_x, new_y))
		cub->player.pos_y = new_y;
}

void	strafe_right(t_cub3d *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.pos_x + cub->player.plane_x * cub->player.move_speed;
	new_y = cub->player.pos_y + cub->player.plane_y * cub->player.move_speed;
	if (!is_wall_bonus(cub, new_x, cub->player.pos_y))
		cub->player.pos_x = new_x;
	if (!is_wall_bonus(cub, cub->player.pos_x, new_y))
		cub->player.pos_y = new_y;
}
