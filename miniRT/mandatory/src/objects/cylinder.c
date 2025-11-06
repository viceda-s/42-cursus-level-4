/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg.>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:00:06 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/04 14:00:06 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:09:33 by rbaldin           #+#    #+#             */
/*   Updated: 2025/10/27 20:01:08 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	parsing_cylinder(t_scene *scene_cylinder, char *line_data_cylinder)
{
	char	*ptr_cy;
	t_cy	*cyl;

	ptr_cy = line_data_cylinder;
	ptr_cy += 2;
	cyl = (t_cy *)getting_latest_object(scene_cylinder, CYLINDER);
	if (!cyl)
		return (1);
	skipping_emptiness(&ptr_cy);
	cyl->data.v = parse_vector(&ptr_cy);
	cyl->data.nov = parse_vector(&ptr_cy);
	cyl->data.nov = vector_normalize(cyl->data.nov);
	if (cyl->data.nov.x < -1.0 || cyl->data.nov.x > 1.0 || \
cyl->data.nov.y < -1.0 || cyl->data.nov.y > 1.0 || cyl->data.nov.z < -1.0 || \
cyl->data.nov.z > 1.0)
		return (1);
	cyl->d = ft_atof_dp(&ptr_cy);
	skipping_emptiness(&ptr_cy);
	cyl->h = ft_atof_dp(&ptr_cy);
	if (cyl->d <= 0.0 || cyl->h <= 0.0)
		return (1);
	skipping_emptiness(&ptr_cy);
	if (parse_color(&ptr_cy, &cyl->data))
		return (1);
	if (*ptr_cy != '\0')
		return (1);
	return (0);
}
