/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:30:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/12/02 15:58:31 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parse_texture(t_cub3d *cub, char *line, int tex_index)
{
	char	*path;

	if (cub->parse.tex_paths[tex_index])
		err_exit(cub, ERR_DUP_ELEMENT);
	path = trim_spaces(line);
	if (!path || *path == '\0')
		err_exit(cub, ERR_TEX_PATH);
	cub->parse.tex_paths[tex_index] = ft_strdup(path);
	if (!cub->parse.tex_paths[tex_index])
		err_exit(cub, ERR_MALLOC);
}
