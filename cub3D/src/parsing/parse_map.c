/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:30:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/12/02 15:58:31 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_map_line(char *line)
{
	int	i;

	if (!line || *line == '\0')
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

static char	**realloc_grid(t_cub3d *cub, char *line)
{
	char	**new_grid;
	int		i;

	new_grid = malloc(sizeof(char *) * (cub->map.height + 2));
	if (!new_grid)
		err_exit(cub, ERR_MALLOC);
	i = 0;
	while (i < cub->map.height)
	{
		new_grid[i] = cub->map.grid[i];
		i++;
	}
	new_grid[cub->map.height] = ft_strdup(line);
	if (!new_grid[cub->map.height])
	{
		free(new_grid);
		err_exit(cub, ERR_MALLOC);
	}
	new_grid[cub->map.height + 1] = NULL;
	free(cub->map.grid);
	return (new_grid);
}

void	add_map_line(t_cub3d *cub, char *line)
{
	int	len;

	cub->map.grid = realloc_grid(cub, line);
	cub->map.height++;
	len = ft_strlen(line);
	if (len > cub->map.width)
		cub->map.width = len;
}
