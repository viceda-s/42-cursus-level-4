/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 00:00:00 by rbaldin           #+#    #+#             */
/*   Updated: 2025/10/27 21:06:37 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parsing_ambient(t_scene *sc1, char *line_data1)
{
	char	*ptr1;

	ptr1 = line_data1;
	if (*ptr1 >= 'A' && *ptr1 <= 'Z')
		ptr1++;
	sc1->ambient.ratio = ft_atof_dp(&ptr1);
	if (sc1->ambient.ratio < 0.0 || sc1->ambient.ratio > 1.0)
		return (1);
	skipping_emptiness(&ptr1);
	sc1->ambient.colours.r = ft_atoi_dp(&ptr1);
	skip_comma(&ptr1);
	sc1->ambient.colours.g = ft_atoi_dp(&ptr1);
	skip_comma(&ptr1);
	sc1->ambient.colours.b = ft_atoi_dp(&ptr1);
	skipping_emptiness(&ptr1);
	if (*ptr1 != '\0')
		return (1);
	return (0);
}

int	parsing_camera(t_scene *sc2, char *line_data2)
{
	char		*ptr2;
	t_vector	world_up;

	ptr2 = line_data2;
	ptr2++;
	extracting_xyz(sc2, &ptr2, 'c');
	extracting_nov_cam(sc2, &ptr2);
	sc2->camera.forward = vector_normalize(sc2->camera.forward);
	world_up = vector_create(0, 1, 0);
	if (fabs(sc2->camera.forward.x) == 0 && fabs(sc2->camera.forward.z) == 0)
		world_up = vector_create(0, 0, (sc2->camera.forward.y > 0) * -1
				+ (sc2->camera.forward.y <= 0));
	sc2->camera.right = vector_normalize(vector_cross(world_up,
				sc2->camera.forward));
	sc2->camera.up = vector_normalize(vector_cross(sc2->camera.forward,
				sc2->camera.right));
	skipping_emptiness(&ptr2);
	sc2->camera.fov = ft_atoi_dp(&ptr2);
	if (sc2->camera.fov < 0 || sc2->camera.fov > 180)
		return (1);
	skipping_emptiness(&ptr2);
	if (*ptr2 != '\0')
		return (1);
	return (0);
}

int	parsing_light(t_scene *sc3, char *line_data3)
{
	char	*ptr3;

	ptr3 = line_data3;
	ptr3++;
	extracting_xyz(sc3, &ptr3, 'l');
	sc3->light.br = ft_atof_dp(&ptr3);
	if (sc3->light.br < 0.0 || sc3->light.br > 1.0)
		return (1);
	skipping_emptiness(&ptr3);
	sc3->light.coord.r = ft_atoi_dp(&ptr3);
	skip_comma(&ptr3);
	sc3->light.coord.g = ft_atoi_dp(&ptr3);
	skip_comma(&ptr3);
	sc3->light.coord.b = ft_atoi_dp(&ptr3);
	if (sc3->light.coord.r < 0 || sc3->light.coord.r > 255
		|| sc3->light.coord.g < 0 || sc3->light.coord.g > 255
		|| sc3->light.coord.b < 0 || sc3->light.coord.b > 255)
		return (1);
	skipping_emptiness(&ptr3);
	if (*ptr3 != '\0')
		return (1);
	return (0);
}

int	parsing_objects(t_scene *sc4, char *line_data4)
{
	if (ft_strncmp(line_data4, "sp ", 3) == 0)
	{
		if (creating_object(sc4, SPHERE, sizeof(t_sp)))
			return (parsing_sphere(sc4, line_data4));
		return (1);
	}
	else if (ft_strncmp(line_data4, "pl ", 3) == 0)
	{
		if (creating_object(sc4, PLANE, sizeof(t_gd)))
			return (parsing_plane(sc4, line_data4));
		return (1);
	}
	else if (ft_strncmp(line_data4, "cy ", 3) == 0)
	{
		if (creating_object(sc4, CYLINDER, sizeof(t_cy)))
			return (parsing_cylinder(sc4, line_data4));
		return (1);
	}
	else
		return (1);
}
