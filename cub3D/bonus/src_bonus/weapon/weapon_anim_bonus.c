/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_anim_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:30:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 14:35:55 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"
#include <math.h>

static void	update_fire_anim(t_cub3d *cub)
{
	cub->weapon.tick_count++;
	if (cub->weapon.tick_count >= WEAPON_FIRE_TICK)
	{
		cub->weapon.tick_count = 0;
		cub->weapon.current_frame++;
		if (cub->weapon.current_frame >= WEAPON_TOTAL_FRAMES)
		{
			cub->weapon.is_shooting = 0;
			cub->weapon.current_frame = 0;
		}
	}
}

static void	update_walk_anim(t_cub3d *cub)
{
	int	walk_start;
	int	walk_end;

	walk_start = WEAPON_IDLE_FRAMES;
	walk_end = WEAPON_IDLE_FRAMES + WEAPON_WALK_FRAMES;
	cub->weapon.tick_count++;
	if (cub->weapon.tick_count >= WEAPON_WALK_TICK)
	{
		cub->weapon.tick_count = 0;
		cub->weapon.current_frame++;
		if (cub->weapon.current_frame >= walk_end)
			cub->weapon.current_frame = walk_start;
	}
}

static void	update_weapon_bob(t_cub3d *cub)
{
	double	bob_sin;

	if (cub->weapon.is_walking && !cub->weapon.is_shooting)
	{
		cub->weapon.bob_time += BOB_SPEED;
		cub->weapon.bob_x = (int)(sin(cub->weapon.bob_time) * BOB_AMOUNT_X);
		bob_sin = fabs(sin(cub->weapon.bob_time * 2));
		cub->weapon.bob_y = (int)(bob_sin * BOB_AMOUNT_Y);
	}
	else
	{
		cub->weapon.bob_time = 0.0;
		cub->weapon.bob_x = 0;
		cub->weapon.bob_y = 0;
	}
}

void	update_weapon(t_cub3d *cub)
{
	update_weapon_bob(cub);
	if (cub->weapon.is_shooting)
		return (update_fire_anim(cub));
	if (cub->weapon.is_walking)
		return (update_walk_anim(cub));
	cub->weapon.current_frame = 0;
}
