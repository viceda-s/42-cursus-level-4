/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 00:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 14:49:46 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	calc_target_distance(t_cub3d *cub, t_target *target)
{
	double	dx;
	double	dy;

	dx = target->pos_x - cub->player.pos_x;
	dy = target->pos_y - cub->player.pos_y;
	target->distance = sqrt(dx * dx + dy * dy);
}

void	prepare_sprites(t_cub3d *cub)
{
	int	i;

	if (!cub->targets || !cub->sprites)
		return ;
	i = 0;
	while (i < cub->target_count)
	{
		calc_target_distance(cub, &cub->targets[i]);
		cub->sprites[i].x = cub->targets[i].pos_x;
		cub->sprites[i].y = cub->targets[i].pos_y;
		cub->sprites[i].tex = get_target_sprite_index(&cub->targets[i]);
		cub->sprites[i].distance = cub->targets[i].distance;
		i++;
	}
	cub->sprite_count = cub->target_count;
}

void	sort_sprites(t_sprite *sprites, int count)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (sprites[j].distance < sprites[j + 1].distance)
			{
				tmp = sprites[j];
				sprites[j] = sprites[j + 1];
				sprites[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	render_sprites(t_cub3d *cub, double *z_buffer)
{
	int	i;

	if (!cub->sprites || cub->sprite_count == 0)
		return ;
	prepare_sprites(cub);
	sort_sprites(cub->sprites, cub->sprite_count);
	i = 0;
	while (i < cub->sprite_count)
	{
		draw_sprite(cub, &cub->sprites[i], z_buffer);
		i++;
	}
}
