/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:22:48 by rbaldin           #+#    #+#             */
/*   Updated: 2025/10/31 15:14:30 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt_bonus.h"

static t_gd	*extracting_xyz_pl(t_scene *scene_coord, char **nums)
{
	t_gd		*pl;
	t_vector	tmp;

	pl = (t_gd *)getting_latest_object(scene_coord, PLANE);
	if (!pl)
		return (NULL);
	tmp = parse_vector(nums);
	pl->v = tmp;
	// pl->v.x = ft_atof_dp(nums);
	// skip_comma(nums);
	// pl->v.y = ft_atof_dp(nums);
	// skip_comma(nums);
	// pl->v.z = ft_atof_dp(nums);
	// skipping_emptiness(nums);
	tmp = parse_vector(nums);
	// pl->nov.x = ft_atof_dp(nums);
	// skip_comma(nums);
	// pl->nov.y = ft_atof_dp(nums);
	// skip_comma(nums);
	// pl->nov.z = ft_atof_dp(nums);
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
	// parse_color(pla, ptr_pl);
	pla->r = ft_atoi_dp(&ptr_pl);
	skip_comma(&ptr_pl);
	pla->g = ft_atoi_dp(&ptr_pl);
	skip_comma(&ptr_pl);
	pla->b = ft_atoi_dp(&ptr_pl);
	if (pla->r < 0 || pla->r > 255 || pla->b < 0 || pla->b > 255 || \
pla->g < 0 || pla->g > 255)
		return (1);
	parse_checker_plane(&ptr_pl, pla);
	if (*ptr_pl != '\0')
		return (1);
	return (0);
}
