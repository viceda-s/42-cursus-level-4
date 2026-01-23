/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target_textures_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 14:42:55 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	load_single_target_tex(t_cub3d *cub, char *path, int i)
{
	cub->target_tex[i].img = mlx_xpm_file_to_image(cub->mlx,
			path, &cub->target_tex[i].width, &cub->target_tex[i].height);
	if (!cub->target_tex[i].img)
	{
		ft_putstr_fd("Warning: Failed to load target texture: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return ;
	}
	cub->target_tex[i].addr = mlx_get_data_addr(cub->target_tex[i].img,
			&cub->target_tex[i].bpp, &cub->target_tex[i].line_len,
			&cub->target_tex[i].endian);
}

void	load_target_textures(t_cub3d *cub)
{
	load_single_target_tex(cub, "./assets/sprites/target/target.xpm", 0);
	load_single_target_tex(cub, "./assets/sprites/target/target_hit.xpm", 1);
}
