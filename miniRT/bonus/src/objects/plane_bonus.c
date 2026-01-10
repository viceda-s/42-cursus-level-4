/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:22:48 by rbaldin           #+#    #+#             */
/*   Updated: 2025/11/06 11:57:27 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_gd	*extracting_xyz_pl(t_scene *scene_coord, char **nums)
{
	t_gd		*pl;
	t_vector	tmp;

	pl = (t_gd *)getting_latest_object(scene_coord, PLANE);
	if (!pl)
		return (NULL);
	tmp = parse_vector(nums);
	pl->v = tmp;
	tmp = parse_vector(nums);
	pl->nov = vector_normalize(tmp);
	return (pl);
}

int	parsing_plane(t_scene *scene_plane, char *line_data_plane)
{
	char	*ptr_pl;
	t_gd	*pla;

	ptr_pl = line_data_plane;
	ptr_pl += 2;
	pla = extracting_xyz_pl(scene_plane, &ptr_pl);
	if (!pla)
		return (1);
	if (pla->nov.z < -1.0 || pla->nov.z > 1.0 || pla->nov.x < -1.0 || \
pla->nov.x > 1.0 || pla->nov.y < -1.0 || pla->nov.y > 1.0)
		return (1);
	skipping_emptiness(&ptr_pl);
	if (parse_color(&ptr_pl, pla))
		return (1);
	parse_texture_map(&ptr_pl, &pla->texture);
	parse_bump_map(&ptr_pl, &pla->bump_map);
	parse_checker(&ptr_pl, &pla->checker);
	parse_bump(&ptr_pl, &pla->has_bump, &pla->bump_strength, &pla->bump_uv);
	skipping_emptiness(&ptr_pl);
	if (*ptr_pl != '\0')
		return (1);
	return (0);
}
