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

	(void)argc;
	(void)argv;
	
	if (!init_minirt_basic(&data))
	{
		write(2, "Erro ao inicializar MinilibX\n", 29);
		return (1);
	}
	
	render_test_scene(&data);
	init_event(&data);
	
	write(1, "=== miniRT Teste ===\n", 21);
	write(1, "ESC ou Q - Sair\n", 16);
	write(1, "X (fechar) - Sair\n", 18);
	
	mlx_loop(data.mlx);
	return (0);
}
