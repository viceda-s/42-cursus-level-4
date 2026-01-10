/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:22:48 by rbaldin           #+#    #+#             */
/*   Updated: 2025/10/27 18:06:26 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	parsing_plane(t_scene *scene_plane, char *line_data_plane)
{
	char	*ptr_pl;
	t_gd	*pla;

	ptr_pl = line_data_plane;
	ptr_pl += 2;
	pla = (t_gd *)getting_latest_object(scene_plane, PLANE);
	if (!pla)
		return (1);
	skipping_emptiness(&ptr_pl);
	pla->v = parse_vector(&ptr_pl);
	pla->nov = parse_vector(&ptr_pl);
	pla->nov = vector_normalize(pla->nov);
	if (pla->nov.z < -1.0 || pla->nov.z > 1.0 || pla->nov.x < -1.0
		|| pla->nov.x > 1.0 || pla->nov.y < -1.0 || pla->nov.y > 1.0)
		return (1);
	if (parse_color(&ptr_pl, pla))
		return (1);
	if (*ptr_pl != '\0')
		return (1);
	return (0);
}
