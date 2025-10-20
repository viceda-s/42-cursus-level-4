/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:11:31 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/20 08:32:43 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_scene(t_scene *scene, t_minirt *data) // Main rendering function - renders the entire scene
{
	int			x;
	int			y;
	t_ray		ray;
	t_gd		color;
	t_viewport	viewport;
	
	// Viewpoint setup
	viewport.width = WINDOW_WIDTH;
	viewport.height = WINDOW_HEIGHT;
	viewport.aspect_ratio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	
	// Iterate through each pixel using "while" loops
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			// generate ray for this pixel using "camera_ray"
			ray = camera_ray(scene->cam, x, y, viewport);
			// calculate color for this ray
			color = trace_ray(ray, scene);
			// put a pixel to image
			mlx_pixel_put(data->mlx, data->win, x, y, color_to_int(color));
			x++;
		}
		y++;
	}
	
}
