/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:30:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 10:55:36 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parse_floor_color(t_cub3d *cub, char *line)
{
	if (cub->parse.floor_set)
		err_exit(cub, ERR_DUP_ELEMENT);
	line++;
	cub->floor_color = parse_rgb(cub, line);
	cub->parse.floor_set = 1;
}

void	parse_ceiling_color(t_cub3d *cub, char *line)
{
	if (cub->parse.ceiling_set)
		err_exit(cub, ERR_DUP_ELEMENT);
	line++;
	cub->ceiling_color = parse_rgb(cub, line);
	cub->parse.ceiling_set = 1;
}
