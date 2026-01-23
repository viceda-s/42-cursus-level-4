/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:55:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 13:20:12 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	cleanup_target_textures(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (cub->target_tex[i].img && cub->mlx)
			mlx_destroy_image(cub->mlx, cub->target_tex[i].img);
		cub->target_tex[i].img = NULL;
		i++;
	}
}

void	cleanup_weapon(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < WEAPON_TOTAL_FRAMES)
	{
		if (cub->weapon.sprites[i].img && cub->mlx)
			mlx_destroy_image(cub->mlx, cub->weapon.sprites[i].img);
		cub->weapon.sprites[i].img = NULL;
		i++;
	}
}

void	cleanup_game_objects(t_cub3d *cub)
{
	if (cub->doors)
		free(cub->doors);
	cub->doors = NULL;
	if (cub->targets)
		free(cub->targets);
	cub->targets = NULL;
	if (cub->sprites)
		free(cub->sprites);
	cub->sprites = NULL;
}
