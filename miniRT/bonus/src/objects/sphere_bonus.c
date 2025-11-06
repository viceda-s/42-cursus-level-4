/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:26:24 by rbaldin           #+#    #+#             */
/*   Updated: 2025/11/06 11:57:25 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_sp	*extracting_xyz_sph(t_scene *scene_coord, char **nums)
{
	t_sp		*sp;
	t_vector	tmp;

	sp = (t_sp *)getting_latest_object(scene_coord, SPHERE);
	if (!sp)
		return (NULL);
	tmp = parse_vector(nums);
	sp->coord_colours.v = tmp;
	return (sp);
}

int	parsing_sphere(t_scene *scene_sphere, char *line_data_sphere)
{
	char	*ptr_sp;
	t_sp	*sphe;

	ptr_sp = line_data_sphere;
	ptr_sp += 2;
	sphe = extracting_xyz_sph(scene_sphere, &ptr_sp);
	if (!sphe)
		return (1);
	sphe->d = ft_atof_dp(&ptr_sp);
	if (parse_color(&ptr_sp, &sphe->coord_colours))
		return (1);
	if (sphe->d <= 0.0)
		return (1);
	parse_texture_map(&ptr_sp, &sphe->texture);
	parse_bump_map(&ptr_sp, &sphe->bump_map);
	parse_checker(&ptr_sp, &sphe->coord_colours.checker);
	parse_bump(&ptr_sp, &sphe->coord_colours.has_bump,
		&sphe->coord_colours.bump_strength, &sphe->coord_colours.bump_uv);
	skipping_emptiness(&ptr_sp);
	if (*ptr_sp != '\0')
		return (1);
	return (0);
}
