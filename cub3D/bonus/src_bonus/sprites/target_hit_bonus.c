/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target_hit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 13:04:46 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	is_target_in_crosshair(t_cub3d *cub, t_target *target, double dist)
{
	double	dx;
	double	dy;
	double	dot_product;
	double	angle;

	dx = target->pos_x - cub->player.pos_x;
	dy = target->pos_y - cub->player.pos_y;
	dx /= dist;
	dy /= dist;
	dot_product = dx * cub->player.dir_x + dy * cub->player.dir_y;
	if (dot_product <= 0)
		return (0);
	angle = acos(dot_product);
	if (angle < 0.1 && dist < 20.0)
		return (1);
	return (0);
}

static void	hit_target(t_cub3d *cub, t_target *target)
{
	target->state = TARGET_HIT;
	cub->score += 100;
}

static int	try_hit_target(t_cub3d *cub, int i)
{
	double	dx;
	double	dy;
	double	dist;

	dx = cub->targets[i].pos_x - cub->player.pos_x;
	dy = cub->targets[i].pos_y - cub->player.pos_y;
	dist = sqrt(dx * dx + dy * dy);
	if (is_target_in_crosshair(cub, &cub->targets[i], dist))
	{
		hit_target(cub, &cub->targets[i]);
		return (1);
	}
	return (0);
}

void	check_target_hit(t_cub3d *cub)
{
	int	i;

	if (!cub->targets)
		return ;
	i = 0;
	while (i < cub->target_count)
	{
		if (cub->targets[i].state == TARGET_ACTIVE && try_hit_target(cub, i))
			break ;
		i++;
	}
}

void	draw_score(t_cub3d *cub)
{
	char	*score_str;
	char	*num_str;

	num_str = ft_itoa(cub->score);
	if (!num_str)
		return ;
	score_str = ft_strjoin("Score: ", num_str);
	free(num_str);
	if (!score_str)
		return ;
	mlx_string_put(cub->mlx, cub->win, WIN_WIDTH - 150, 30,
		0xFFFFFF, score_str);
	free(score_str);
}
