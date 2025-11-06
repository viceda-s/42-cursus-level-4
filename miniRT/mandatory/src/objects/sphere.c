/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:26:24 by rbaldin           #+#    #+#             */
/*   Updated: 2025/10/27 18:23:02 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	parsing_sphere(t_scene *scene_sphere, char *line_data_sphere)
{
	char	*ptr_sp;
	t_sp	*sphe;

	ptr_sp = line_data_sphere;
	ptr_sp += 2;
	sphe = (t_sp *)getting_latest_object(scene_sphere, SPHERE);
	if (!sphe)
		return (1);
	skipping_emptiness(&ptr_sp);
	sphe->coord_colours.v = parse_vector(&ptr_sp);
	sphe->d = ft_atof_dp(&ptr_sp);
	if (sphe->d <= 0.0)
		return (1);
	skipping_emptiness(&ptr_sp);
	if (parse_color(&ptr_sp, &sphe->coord_colours))
		return (1);
	if (*ptr_sp != '\0')
		return (1);
	return (0);
}
