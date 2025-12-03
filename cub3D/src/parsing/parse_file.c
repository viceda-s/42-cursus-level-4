/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:30:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/12/02 16:11:01 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	parse_element(t_cub3d *cub, char *line)
{
	char	*trimmed;

	trimmed = trim_spaces(line);
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		parse_texture(cub, trimmed + 3, TEX_NORTH);
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		parse_texture(cub, trimmed + 3, TEX_SOUTH);
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		parse_texture(cub, trimmed + 3, TEX_WEST);
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		parse_texture(cub, trimmed + 3, TEX_EAST);
	else if (ft_strncmp(trimmed, "F ", 2) == 0)
		parse_floor_color(cub, trimmed + 1);
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
		parse_ceiling_color(cub, trimmed + 1);
	else if (is_map_line(trimmed))
		add_map_line(cub, trimmed);
	else if (!is_empty_line(trimmed))
		err_exit(cub, ERR_FILE_READ);
}

static void	read_file_content(t_cub3d *cub, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		remove_newline(line);
		parse_element(cub, line);
		free(line);
		line = get_next_line(fd);
	}
}

void	parse_file(t_cub3d *cub, char *filename)
{
	int	fd;

	if (!check_extension(filename, ".cub"))
		err_exit(cub, ERR_FILE_EXT);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		err_exit(cub, ERR_FILE_OPEN);
	read_file_content(cub, fd);
	close(fd);
	validate_elements(cub);
	validate_map(cub);
	extract_player(cub);
}
