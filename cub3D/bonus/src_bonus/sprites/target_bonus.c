/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 14:47:34 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	count_targets(t_cub3d *cub)
{
	int	i;
	int	j;

	cub->target_count = 0;
	i = 0;
	while (i < cub->map.height)
	{
		j = 0;
		while (cub->map.grid[i] && cub->map.grid[i][j])
		{
			if (cub->map.grid[i][j] == 'T')
				cub->target_count++;
			j++;
		}
		i++;
	}
}

static void	init_single_target(t_cub3d *cub, int i, int j, int idx)
{
	cub->targets[idx].pos_x = j + 0.5;
	cub->targets[idx].pos_y = i + 0.5;
	cub->targets[idx].state = TARGET_ACTIVE;
	cub->targets[idx].sprite_index = 0;
	cub->targets[idx].distance = 0.0;
	cub->map.grid[i][j] = '0';
}

static void	fill_targets(t_cub3d *cub)
{
	int	i;
	int	j;
	int	idx;

	idx = 0;
	i = -1;
	while (++i < cub->map.height)
	{
		j = -1;
		while (++j < cub->map.width && cub->map.grid[i][j])
		{
			if (cub->map.grid[i][j] == 'T')
				init_single_target(cub, i, j, idx++);
		}
	}
}

void	init_targets(t_cub3d *cub)
{
	count_targets(cub);
	cub->score = 0;
	cub->sprite_count = cub->target_count;
	if (cub->target_count == 0)
	{
		cub->targets = NULL;
		return ;
	}
	cub->targets = malloc(sizeof(t_target) * cub->target_count);
	if (!cub->targets)
		err_exit(cub, ERR_MALLOC);
	cub->sprites = malloc(sizeof(t_sprite) * cub->target_count);
	if (!cub->sprites)
		err_exit(cub, ERR_MALLOC);
	fill_targets(cub);
}

int	get_target_sprite_index(t_target *target)
{
	if (target->state == TARGET_HIT)
		return (1);
	return (0);
}
