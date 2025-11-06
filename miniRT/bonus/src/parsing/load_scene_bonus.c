/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:50:47 by rbaldin           #+#    #+#             */
/*   Updated: 2025/11/05 20:06:47 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	process_ambient_line(t_scene *scn, char *lin)
{
	if (parsing_ambient(scn, lin))
		return (1);
	scn->checklist.ambient_set++;
	return (0);
}

static t_scene	*processing_trimmed_line(char *trim, t_scene *scn, int fd)
{
	if (*trim == 'A')
	{
		if (process_ambient_line(scn, trim))
		{
			free(trim);
			return (error_case(scn, fd, "Error: Invalid ambient line\n"));
		}
	}
	else
	{
		if (!continuing_processing(trim, scn, &fd))
		{
			free(trim);
			return (NULL);
		}
	}
	return (scn);
}

static t_scene	*processing_lines(t_scene *scn, int fd)
{
	char	*line;
	char	*trimmed;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		trimmed = ft_strtrim(line, " \t\v\f\r\n");
		free(line);
		if (!trimmed)
			return (error_case(scn, fd, "Error: Malloc failed\n"));
		if (*trimmed != '\0' && *trimmed != '#')
		{
			scn = processing_trimmed_line(trimmed, scn, fd);
			if (!scn)
			{
				free(trimmed);
				return (NULL);
			}
		}
		free(trimmed);
	}
	close(fd);
	return (scn);
}

t_scene	*creating_scene(char *filename)
{
	t_scene	*scene;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (NULL);
	}
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
	{
		close(fd);
		return (NULL);
	}
	return (processing_lines(scene, fd));
}

t_scene	*load_scene(char *filename)
{
	t_scene	*scene;

	scene = creating_scene(filename);
	if (!scene)
		return (NULL);
	if (scene->checklist.ambient_set != 1
		|| scene->checklist.camera_set != 1
		|| scene->checklist.light_set < 1)
	{
		cleanup_scene(scene);
		return (NULL);
	}
	return (scene);
}
