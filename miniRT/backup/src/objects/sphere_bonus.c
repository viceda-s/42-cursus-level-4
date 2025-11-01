/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg.>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:06:22 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/31 20:06:26 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:26:24 by rbaldin           #+#    #+#             */
/*   Updated: 2025/10/31 15:15:39 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt_bonus.h"

static t_sp	*extracting_xyz_sph(t_scene *scene_coord, char **nums)
{
	t_sp		*sp;
	t_vector	tmp;

	sp = (t_sp *)getting_latest_object(scene_coord, SPHERE);
	if (!sp)
		return (NULL);
	tmp = parse_vector(nums);
	sp->coord_colours.v = tmp;
	// sp->coord_colours.v.x = ft_atof_dp(nums);
	// skip_comma(nums);
	// sp->coord_colours.v.y = ft_atof_dp(nums);
	// skip_comma(nums);
	// sp->coord_colours.v.z = ft_atof_dp(nums);
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
	sphe->coord_colours.r = ft_atoi_dp(&ptr_sp);
	skip_comma(&ptr_sp);
	sphe->coord_colours.g = ft_atoi_dp(&ptr_sp);
	skip_comma(&ptr_sp);
	sphe->coord_colours.b = ft_atoi_dp(&ptr_sp);
	if (sphe->d <= 0.0 || sphe->coord_colours.r < 0 || \
sphe->coord_colours.r > 255 || sphe->coord_colours.g < 0 || \
sphe->coord_colours.g > 255 || sphe->coord_colours.b < 0 || \
sphe->coord_colours.b > 255)
		return (1);
	parse_checker_sphere(&ptr_sp, sphe);
	if (*ptr_sp != '\0')
		return (1);
	return (0);
}
