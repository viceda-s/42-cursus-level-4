/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:06:27 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/24 19:21:03 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_minirt_basic(t_minirt *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (0);

	data->win = mlx_new_window(data->mlx, 800, 600, "miniRT");
	if (!data->win)
		return (0);

	data->img = mlx_new_image(data->mlx, 800, 600);
	if (!data->img)
		return (0);

	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
									&data->line_length, &data->endian);
	data->scene = NULL;
	return (1);
}

void	put_pixel(t_minirt *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= 800 || y < 0 || y >= 600)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	render_test_scene(t_minirt *data)
{
	int	x, y, color;

	y = 0;
	while (y < 600)
	{
		x = 0;
		while (x < 800)
		{
			color = (x * 255 / 800) << 16 | (y * 255 / 600) << 8 | 100;
			put_pixel(data, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	cleanup_scene(void *scene)
{
	if (scene)
		free(scene);
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
	printf("Loading scene...\n");
	scene = load_scene(argv[1]);
	if (!scene)
	{
		printf("Error\nFailed to parse scene file\n");
		return (1);
	}
	printf("Scene loaded successfully!\n");
	if (!init_minirt_basic(&data))
	{
		printf("Error\nFailed to initialize miniRT\n");
		cleanup_scene(scene);
		return (1);
	}
	printf("MiniRT initialized!\n");
	data.scene = scene;
	
	init_event(&data);
	printf("Rendering scene...\n");
	render_scene(scene, &data);
	printf("Putting image to window...\n");
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	printf("Starting MLX loop...\n");
	mlx_loop(data.mlx);
	return (0);
}