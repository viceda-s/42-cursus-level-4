/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/12/16 20:15:02 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	parse_bonus_element(t_cub3d *cub, char *trimmed)
{
	int	door_num;

	if (trimmed[0] == 'D' && ft_isdigit(trimmed[1]) && trimmed[2] == ' ')
	{
		door_num = trimmed[1] - '0';
		if (door_num >= 1 && door_num <= 9)
		{
			parse_texture(cub, trimmed + 3, TEX_DOOR_START + door_num - 1);
			return (1);
		}
	}
	return (0);
}

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
	else if (parse_bonus_element(cub, trimmed))
		return ;
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
}
