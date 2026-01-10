/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:10:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/03 16:12:06 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_scene	*error_case(t_scene *scene_error, int fd_error, const char *l_error)
{
	if (fd_error >= 0)
		close(fd_error);
	if (l_error)
		ft_putstr_fd((char *)l_error, 2);
	cleanup_scene(scene_error);
	return (NULL);
}

t_scene	*continuing_processing(char *line, t_scene *scn, int *fdesc)
{
	if (*line == 'C')
	{
		if (parsing_camera(scn, line))
			return (error_case(scn, *fdesc, "Error: Invalid camera line\n"));
		scn->checklist.camera_set++;
	}
	else if (*line == 'L')
	{
		if (parsing_light(scn, line))
			return (error_case(scn, *fdesc, "Error: Invalid light line\n"));
		scn->checklist.light_set++;
	}
	else
	{
		if (parsing_objects(scn, line))
			return (error_case(scn, *fdesc, "Error: Invalid object line\n"));
	}
	return (scn);
}
