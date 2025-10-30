/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:06:27 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/27 20:00:58 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	init_minirt_basic(t_minirt *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->win_width = WINDOW_WIDTH;
	data->win_height = WINDOW_HEIGHT;
	data->win = mlx_new_window(data->mlx, data->win_width,
			data->win_height, "miniRT");
	if (!data->win)
		return (1);
	data->img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	if (!data->img)
	{
		mlx_destroy_window(data->mlx, data->win);
		return (1);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	return (0);
}

void	put_pixel(t_minirt *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= data->win_width || y < 0 || y >= data->win_height)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	render_test_scene(t_minirt *data)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			color = (x * 255 / data->win_width) << 16
				| (y * 255 / data->win_height) << 8 | 100;
			put_pixel(data, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	cleanup_scene(t_scene *scene)
{
	ft_lstclear(&scene->objects_list, free_object);
	free(scene);
	scene = NULL;
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
	scene = load_scene(argv[1]);
	if (!scene)
	{
		printf("Error\nFailed to parse scene file\n");
		return (1);
	}
	if (init_minirt_basic(&data) != 0)
	{
		printf("Error\nFailed to initialize miniRT\n");
		cleanup_scene(scene);
		return (1);
	}
	data.scene = scene;
	init_event(&data);
	render_scene(scene, &data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
}
