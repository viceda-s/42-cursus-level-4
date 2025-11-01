/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:11:31 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/30 09:03:11 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * @brief Renders the entire scene by tracing rays through each pixel.
 *
 * This function iterates through every pixel in the window, generates a camera
 * ray for each pixel, traces that ray through the scene to determine the 
 * color, and puts the resulting color to the pixel on screen. 
 * The viewport is calculated based on the window dimensions and aspect ratio.
 *
 * @param scene The scene containing all objects, camera,
 *        and lighting information.
 * @param data The miniRT data structure containing the MLX image buffer.
 */
void	render_scene(t_scene *scene, t_minirt *data)
{
	int			x;
	int			y;
	t_gd		color;
	t_viewport	viewport;

	viewport.width = WINDOW_WIDTH;
	viewport.height = WINDOW_HEIGHT;
	viewport.aspect_ratio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			color = get_pixel_color_with_aa(scene, x, y, viewport);
			put_pixel(data, x, y, (color.r << 16) | (color.g << 8) | color.b);
			x++;
		}
		y++;
	}
}
