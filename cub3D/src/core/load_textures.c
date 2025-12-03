/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:10:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/12/02 16:11:02 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	load_single_texture(t_cub3d *cub, int index)
{
	if (!cub->parse.tex_paths[index])
		err_exit(cub, ERR_TEX_PATH);
	cub->tex[index].img = mlx_xpm_file_to_image(cub->mlx,
			cub->parse.tex_paths[index],
			&cub->tex[index].width, &cub->tex[index].height);
	if (!cub->tex[index].img)
		err_exit(cub, ERR_TEX_LOAD);
	cub->tex[index].addr = mlx_get_data_addr(cub->tex[index].img,
			&cub->tex[index].bpp, &cub->tex[index].line_len,
			&cub->tex[index].endian);
	if (!cub->tex[index].addr)
		err_exit(cub, ERR_TEX_LOAD);
}

void	load_textures(t_cub3d *cub)
{
	load_single_texture(cub, TEX_NORTH);
	load_single_texture(cub, TEX_SOUTH);
	load_single_texture(cub, TEX_EAST);
	load_single_texture(cub, TEX_WEST);
}
