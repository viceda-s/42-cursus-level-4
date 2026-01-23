/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:55:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 12:35:04 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	cleanup_textures(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (cub->tex[i].img && cub->mlx)
			mlx_destroy_image(cub->mlx, cub->tex[i].img);
		cub->tex[i].img = NULL;
		if (cub->parse.tex_paths[i])
			free(cub->parse.tex_paths[i]);
		cub->parse.tex_paths[i] = NULL;
		i++;
	}
}

static void	cleanup_mlx(t_cub3d *cub)
{
	if (cub->img.img && cub->mlx)
		mlx_destroy_image(cub->mlx, cub->img.img);
	cub->img.img = NULL;
	if (cub->win && cub->mlx)
		mlx_destroy_window(cub->mlx, cub->win);
	cub->win = NULL;
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	cub->mlx = NULL;
}

void	cleanup(t_cub3d *cub)
{
	if (!cub)
		return ;
	cleanup_game_objects(cub);
	cleanup_target_textures(cub);
	cleanup_weapon(cub);
	cleanup_textures(cub);
	free_array(cub->map.grid);
	cub->map.grid = NULL;
	cleanup_mlx(cub);
}
