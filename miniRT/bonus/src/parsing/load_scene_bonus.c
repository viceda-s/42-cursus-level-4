/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:50:47 by rbaldin           #+#    #+#             */
/*   Updated: 2025/10/26 18:02:24 by rbaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Your program must take as its first argument a scene description file with
the .rt extension.
◦ Each type of element can be separated by one or more line breaks. (check)
◦ Each type of information from an element can be separated by one or more
spaces. (check)
◦ Each type of element can be set in any order in the file. (check)
◦ Elements defined by a capital letter can only be declared once in the scene.
(check)
 */

#include "minirt_bonus.h"

static t_scene	*error_case(t_scene *scene_error, int fd_error, char *l_error)
{
	close(fd_error);
	free(l_error);
	cleanup_scene(scene_error);
	return (NULL);
}

static t_scene	*continuing_processing(char *line, t_scene *scn, int *fdesc)
{
	if (*line == 'C')
	{
		if (parsing_camera(scn, line))
			return (error_case(scn, *fdesc, line));
		scn->checklist.camera_set++;
	}
	else if (*line == 'L')
	{
		if (parsing_light(scn, line))
			return (error_case(scn, *fdesc, line));
		scn->checklist.light_set++;
	}
	else
	{
		if (parsing_objects(scn, line))
			return (error_case(scn, *fdesc, line));
	}
	free(line);
	return (scn);
}

// Inside t_scene, allocate arrays for objects/lights based on parsed counts
static t_scene	*processing_lines(t_scene *scn, int *fdesc, char *lin)
{
	char	*trimmed;

	while (1)
	{
		lin = get_next_line(*fdesc);
		if (!lin)
			break ;
		trimmed = lin;
		while (*trimmed == ' ' || *trimmed == '\t')
			trimmed++;
		if (*trimmed == '\n' || *trimmed == '\0' || *trimmed == '#')
		{
			free(lin);
			continue ;
		}
		if (*lin == 'A')
		{
			if (parsing_ambient(scn, lin))
				return (error_case(scn, *fdesc, lin));
			scn->checklist.ambient_set++;
			free(lin);
		}
		else
		{
			if (NULL == continuing_processing(lin, scn, fdesc))
				return (NULL);
		}
	}
	close(*fdesc);
	return (scn);
}

t_scene	*creating_scene(char *filename)
{
	char	*line;
	t_scene	*scene;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	scene = malloc(sizeof(t_scene));
	if (!scene)
	{
		close(fd);
		return (NULL);
	}
	line = NULL;
	ft_bzero(scene, sizeof(t_scene));
	scene->checklist.ambient_set = 0;
	scene->checklist.camera_set = 0;
	scene->checklist.light_set = 0;
	return (processing_lines(scene, &fd, line));
}

t_scene	*load_scene(char *filename)
{
	t_scene	*scene;

	scene = creating_scene(filename);
	if (!scene)
		return (NULL);
	if (scene->checklist.ambient_set != 1
		|| scene->checklist.camera_set != 1
		|| scene->checklist.light_set != 1)
	{
		cleanup_scene(scene);
		return (NULL);
	}
	return (scene);
}
