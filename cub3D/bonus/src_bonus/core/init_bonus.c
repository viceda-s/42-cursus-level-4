/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:55:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 13:04:46 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	init_parse(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		cub->tex[i].img = NULL;
		cub->tex[i].addr = NULL;
		cub->parse.tex_paths[i] = NULL;
		i++;
	}
	cub->parse.floor_set = 0;
	cub->parse.ceiling_set = 0;
	cub->parse.player_count = 0;
	cub->parse.player_dir = 0;
	cub->parse.player_x = 0;
	cub->parse.player_y = 0;
}

static void	init_keys(t_cub3d *cub)
{
	int	i;

	cub->key_left = 0;
	cub->key_right = 0;
	i = -1;
	while (++i < 256)
		cub->keys[i] = 0;
}

static void	init_bonus_data(t_cub3d *cub)
{
	cub->doors = NULL;
	cub->door_count = 0;
	cub->mouse_enabled = 1;
	cub->last_mouse_x = WIN_WIDTH / 2;
	cub->targets = NULL;
	cub->target_count = 0;
	cub->score = 0;
	cub->sprites = NULL;
	cub->sprite_count = 0;
}

void	init_cub(t_cub3d *cub)
{
	cub->mlx = NULL;
	cub->win = NULL;
	cub->img.img = NULL;
	cub->img.addr = NULL;
	cub->floor_color = 0;
	cub->ceiling_color = 0;
	cub->map.grid = NULL;
	cub->map.width = 0;
	cub->map.height = 0;
	init_parse(cub);
	init_keys(cub);
	init_bonus_data(cub);
	init_weapon(cub);
}

void	init_mlx(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		err_exit(cub, ERR_MLX_INIT);
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!cub->win)
		err_exit(cub, ERR_MLX_WIN);
	cub->img.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub->img.img)
		err_exit(cub, ERR_MLX_IMG);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bpp,
			&cub->img.line_len, &cub->img.endian);
	if (!cub->img.addr)
		err_exit(cub, ERR_MLX_IMG);
	mlx_mouse_hide(cub->mlx, cub->win);
	mlx_mouse_move(cub->mlx, cub->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
}
