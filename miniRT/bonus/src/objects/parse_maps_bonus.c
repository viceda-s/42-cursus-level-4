/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_maps_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 22:15:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/06 11:01:51 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	parse_texture_map(char **ptr, t_texture **texture)
{
	char	*tex_path;

	tex_path = parse_texture_path(ptr);
	if (tex_path)
	{
		*texture = malloc(sizeof(t_texture));
		if (*texture)
			(*texture)->filepath = tex_path;
		else
			free(tex_path);
	}
	else
		*texture = NULL;
}

void	parse_bump_map(char **ptr, t_texture **bump_map)
{
	char	*bump_path;

	bump_path = parse_bump_map_path(ptr);
	if (bump_path)
	{
		*bump_map = malloc(sizeof(t_texture));
		if (*bump_map)
			(*bump_map)->filepath = bump_path;
		else
			free(bump_path);
	}
	else
		*bump_map = NULL;
}
