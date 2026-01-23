/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:30:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 11:02:03 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static const char	*get_error_message(t_error code)
{
	static const char	*messages[] = {
	[ERR_NONE] = "No error",
	[ERR_ARGS] = "Invalid arguments. Usage: ./cub3D <map.cub>",
	[ERR_FILE_EXT] = "Invalid file extension. Use .cub files",
	[ERR_FILE_OPEN] = "Cannot open file",
	[ERR_FILE_READ] = "Error reading file",
	[ERR_MALLOC] = "Memory allocation failed",
	[ERR_MLX_INIT] = "Failed to initialize MLX",
	[ERR_MLX_WIN] = "Failed to create window",
	[ERR_MLX_IMG] = "Failed to create image",
	[ERR_TEX_PATH] = "Invalid texture path",
	[ERR_TEX_LOAD] = "Failed to load texture",
	[ERR_COLOR_FORMAT] = "Invalid color format",
	[ERR_COLOR_RANGE] = "Color values must be 0-255",
	[ERR_MAP_CHAR] = "Invalid character in map",
	[ERR_MAP_PLAYER] = "Map must have exactly one player (N/S/E/W)",
	[ERR_MAP_CLOSED] = "Map is not closed by walls",
	[ERR_MAP_EMPTY] = "Empty or missing map",
	[ERR_DUP_ELEMENT] = "Duplicate element in file",
	[ERR_MISS_ELEMENT] = "Missing required element"
	};

	if (code >= 0 && code <= ERR_MISS_ELEMENT)
		return (messages[code]);
	return ("Unknown error");
}

void	err_msg(t_error code)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd((char *)get_error_message(code), 2);
	ft_putstr_fd("\n", 2);
}

void	err_exit(t_cub3d *cub, t_error code)
{
	err_msg(code);
	cleanup(cub);
	exit(1);
}
