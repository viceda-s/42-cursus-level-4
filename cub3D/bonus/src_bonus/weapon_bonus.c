/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:30:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 13:15:52 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	init_weapon(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < WEAPON_TOTAL_FRAMES)
	{
		cub->weapon.sprites[i].img = NULL;
		cub->weapon.sprites[i].addr = NULL;
		i++;
	}
	cub->weapon.is_shooting = 0;
	cub->weapon.current_frame = 0;
	cub->weapon.tick_count = 0;
}

static void	load_single_weapon(t_cub3d *cub, char *path, int i)
{
	cub->weapon.sprites[i].img = mlx_xpm_file_to_image(cub->mlx,
			path, &cub->weapon.sprites[i].width,
			&cub->weapon.sprites[i].height);
	if (!cub->weapon.sprites[i].img)
	{
		ft_putstr_fd("Warning: Failed to load weapon: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return ;
	}
	cub->weapon.sprites[i].addr = mlx_get_data_addr(
			cub->weapon.sprites[i].img, &cub->weapon.sprites[i].bpp,
			&cub->weapon.sprites[i].line_len, &cub->weapon.sprites[i].endian);
}

void	load_weapon_sprite(t_cub3d *cub)
{
	load_single_weapon(cub, "./assets/sprites/weapon/idle_0.xpm", 0);
	load_single_weapon(cub, "./assets/sprites/weapon/idle_1.xpm", 1);
	load_single_weapon(cub, "./assets/sprites/weapon/idle_2.xpm", 2);
	load_single_weapon(cub, "./assets/sprites/weapon/fire_0.xpm", 3);
	load_single_weapon(cub, "./assets/sprites/weapon/fire_1.xpm", 4);
	load_single_weapon(cub, "./assets/sprites/weapon/fire_2.xpm", 5);
	load_single_weapon(cub, "./assets/sprites/weapon/fire_3.xpm", 6);
	load_single_weapon(cub, "./assets/sprites/weapon/fire_4.xpm", 7);
}

void	shoot_weapon(t_cub3d *cub)
{
	if (cub->weapon.is_shooting)
		return ;
	cub->weapon.is_shooting = 1;
	cub->weapon.current_frame = WEAPON_IDLE_FRAMES;
	cub->weapon.tick_count = 0;
	check_target_hit(cub);
}

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

void	update_weapon(t_cub3d *cub)
{
	if (cub->weapon.is_shooting)
		return (update_fire_anim(cub));
	cub->weapon.tick_count++;
	if (cub->weapon.tick_count >= WEAPON_IDLE_TICK)
	{
		cub->weapon.tick_count = 0;
		cub->weapon.current_frame = (cub->weapon.current_frame + 1)
			% WEAPON_IDLE_FRAMES;
	}
}
