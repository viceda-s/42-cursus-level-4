/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:44:02 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/05 16:52:18 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:06:27 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/03 16:12:06 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	load_and_validate(char *filename, t_scene **scene)
{
	if (!filename)
		return (1);
	*scene = load_scene(filename);
	if (!*scene)
	{
		printf("Error\nFailed to parse scene file\n");
		return (1);
	}
	return (0);
}

static int	setup_render(t_minirt *data, t_scene *scene)
{
	if (init_minirt(data) != 0)
	{
		printf("Error\nFailed to initialize miniRT\n");
		cleanup_scene(scene);
		return (1);
	}
	data->scene = scene;
	data->fast_render = false;
	load_scene_textures(data->mlx, scene);
	init_selection(data->scene);
	init_event(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_minirt	data;
	t_scene		*scene;

	if (argc != 2)
	{
		printf("Usage: ./miniRT <file.rt>\n");
		return (1);
	}
	if (load_and_validate(argv[1], &scene) != 0)
		return (1);
	if (setup_render(&data, scene) != 0)
		return (1);
	render_scene(scene, &data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
}
