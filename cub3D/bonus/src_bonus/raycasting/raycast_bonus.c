/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:10:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/12/13 12:45:28 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	init_ray(t_cub3d *cub, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = cub->player.dir_x + cub->player.plane_x * ray->camera_x;
	ray->dir_y = cub->player.dir_y + cub->player.plane_y * ray->camera_x;
	ray->map_x = (int)cub->player.pos_x;
	ray->map_y = (int)cub->player.pos_y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
	ray->hit_door = 0;
}

void	raycast(t_cub3d *cub)
{
	t_ray	ray;
	int		x;
	double	saved_perp_dist;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(cub, &ray, x);
		calculate_step_and_side_dist(cub, &ray);
		perform_dda(cub, &ray);
		if (ray.hit_door && ray.has_wall_behind)
		{
			saved_perp_dist = ray.perp_wall_dist;
			ray.perp_wall_dist = ray.door_perp_dist;
		}
		calculate_wall_height(&ray);
		calculate_tex_x(cub, &ray);
		if (ray.hit_door && ray.has_wall_behind)
			ray.perp_wall_dist = saved_perp_dist;
		cub->z_buffer[x] = ray.perp_wall_dist;
		draw_column(cub, &ray, x);
		x++;
	}
}
