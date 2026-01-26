/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target_score_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/26 14:00:00 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	draw_score_bar_vertical(t_cub3d *cub, int bar_x, int bar_y)
{
	int	i;
	int	bar_height;
	int	color;

	bar_height = 40;
	i = 0;
	while (i < bar_height)
	{
		if (i < 3 || i >= bar_height - 3)
			color = 0xAA0000;
		else
			color = 0x000000;
		put_pixel(&cub->img, bar_x, bar_y + i, color);
		put_pixel(&cub->img, bar_x + 250 - 1, bar_y + i, color);
		i++;
	}
}

static void	draw_score_bar_horizontal(t_cub3d *cub, int bar_x, int bar_y)
{
	int	i;
	int	bar_width;
	int	color;

	bar_width = 250;
	i = 0;
	while (i < bar_width)
	{
		if (i < 3 || i >= bar_width - 3)
			color = 0xAA0000;
		else
			color = 0x000000;
		put_pixel(&cub->img, bar_x + i, bar_y, color);
		put_pixel(&cub->img, bar_x + i, bar_y + 40 - 1, color);
		i++;
	}
}

static void	draw_score_bar(t_cub3d *cub, int bar_x, int bar_y)
{
	draw_score_bar_vertical(cub, bar_x, bar_y);
	draw_score_bar_horizontal(cub, bar_x, bar_y);
}

static void	draw_score_text(t_cub3d *cub, char *kills_str, char *targets_str)
{
	int	bar_x;
	int	bar_y;

	bar_x = WIN_WIDTH - 270;
	bar_y = 20;
	mlx_string_put(cub->mlx, cub->win, bar_x + 20, bar_y + 28,
		0xFF0000, "SCORE:");
	mlx_string_put(cub->mlx, cub->win, bar_x + 100, bar_y + 28,
		0xFFAA00, kills_str);
	mlx_string_put(cub->mlx, cub->win, bar_x + 140, bar_y + 28,
		0xAAAAAA, "/");
	mlx_string_put(cub->mlx, cub->win, bar_x + 160, bar_y + 28,
		0xCCCCCC, targets_str);
}

void	draw_score(t_cub3d *cub)
{
	char	*kills_str;
	char	*targets_str;
	int		kills;

	draw_score_bar(cub, WIN_WIDTH - 270, 20);
	kills = cub->score / 100;
	kills_str = ft_itoa(kills);
	if (!kills_str)
		return ;
	targets_str = ft_itoa(cub->target_count);
	if (!targets_str)
		return (free(kills_str));
	draw_score_text(cub, kills_str, targets_str);
	free(kills_str);
	free(targets_str);
	if (all_targets_cleared(cub))
		draw_mission_complete(cub);
}
