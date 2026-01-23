/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:30:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 14:35:51 by viceda-s         ###   ########.fr       */
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
	cub->weapon.is_walking = 0;
	cub->weapon.current_frame = 0;
	cub->weapon.tick_count = 0;
	cub->weapon.bob_time = 0.0;
	cub->weapon.bob_x = 0;
	cub->weapon.bob_y = 0;
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
	load_single_weapon(cub, "./assets/sprites/shotgun/idle_1.xpm", 0);
	load_single_weapon(cub, "./assets/sprites/shotgun/walk_1.xpm", 1);
	load_single_weapon(cub, "./assets/sprites/shotgun/walk_2.xpm", 2);
	load_single_weapon(cub, "./assets/sprites/shotgun/fire_1.xpm", 3);
	load_single_weapon(cub, "./assets/sprites/shotgun/fire_2.xpm", 4);
	load_single_weapon(cub, "./assets/sprites/shotgun/fire_3.xpm", 5);
	load_single_weapon(cub, "./assets/sprites/shotgun/fire_4.xpm", 6);
	load_single_weapon(cub, "./assets/sprites/shotgun/fire_5.xpm", 7);
}

void	shoot_weapon(t_cub3d *cub)
{
	if (cub->weapon.is_shooting)
		return ;
	cub->weapon.is_shooting = 1;
	cub->weapon.current_frame = WEAPON_IDLE_FRAMES + WEAPON_WALK_FRAMES;
	cub->weapon.tick_count = 0;
	check_target_hit(cub);
}
