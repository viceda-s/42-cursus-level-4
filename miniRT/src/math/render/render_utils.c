/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:21:32 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/20 08:27:11 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_gd	trace_ray(t_ray ray, t_scene *scene) // Traces a ray through the scene and returns the color using t_gd structure
{
	t_gd	color;
	
	color.r = (int)((ray.direction.x + 1.0f) * 0.5f * 255);
	color.g = (int)((ray.direction.y + 1.0f) * 0.5f * 255);
	color.b = (int)((ray.direction.z + 1.0f) * 0.5f * 255);
	return (color);
}

int	color_to_int(t_gd color) // Converts t_gd color to integer format for MLX
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}
