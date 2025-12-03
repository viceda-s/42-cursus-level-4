/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:55:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/12/02 16:33:13 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	load_single_texture(t_cub3d *cub, int index, int required)
{
	if (!cub->parse.tex_paths[index])
	{
		if (required)
			err_exit(cub, ERR_TEX_PATH);
		return ;
	}
	ft_printf("Loading texture: %s\n", cub->parse.tex_paths[index]);
	cub->tex[index].img = mlx_xpm_file_to_image(cub->mlx,
			cub->parse.tex_paths[index],
			&cub->tex[index].width, &cub->tex[index].height);
	if (!cub->tex[index].img)
	{
		ft_printf("Failed to load: %s\n", cub->parse.tex_paths[index]);
		err_exit(cub, ERR_TEX_LOAD);
	}
	cub->tex[index].addr = mlx_get_data_addr(cub->tex[index].img,
			&cub->tex[index].bpp, &cub->tex[index].line_len,
			&cub->tex[index].endian);
	if (!cub->tex[index].addr)
		err_exit(cub, ERR_TEX_LOAD);
}

void	load_textures(t_cub3d *cub)
{
	load_single_texture(cub, TEX_NORTH, 1);
	load_single_texture(cub, TEX_SOUTH, 1);
	load_single_texture(cub, TEX_EAST, 1);
	load_single_texture(cub, TEX_WEST, 1);
	load_single_texture(cub, TEX_DOOR, 0);
}
