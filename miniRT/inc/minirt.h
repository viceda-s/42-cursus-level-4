/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:30:15 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/10 17:07:44 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../lib/libft/include/libft.h"
# include "../lib/minilibx-linux/mlx.h"

# define ESC_KEY 65307

typedef struct	s_minirt
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*scene;
}				t_minirt;

typedef struct s_gd{ // general data, but also plane
	size_t	r;
	size_t	g;
	size_t	b;
	float	x;
	float	y;
	float	z;
	float	nov_x; // nov = normalized orientation vector
	float	nov_y;
	float	nov_z;
} t_gd;

typedef struct	s_al{ //ambient light
	float	ratio;
	t_gd	colours;
} t_al;


typedef struct s_cam{	// camera
	t_gd	coord_nov;
	float	fov;	// angles
} t_cam;


typedef struct s_l{	//light
	t_gd	coord;
	float	br;	// brightness ratio
} t_l;

typedef	struct s_sp { // sphere
	t_gd	coord_colours;
	float	d;	//diameter;
} t_sp;

typedef struct s_cy {
	t_gd	data;
	float	d;
	float	h; // height
} t_cy;

// event.c
int		exit_program(t_minirt *data);
int		keypress_handler(int key, t_minirt *data);
int		close_window(t_minirt *data);
void	init_event(t_minirt *data);

//main.c
int		init_minirt_basic(t_minirt *data);
void	render_test_scene(t_minirt *data);
void	put_pixel(t_minirt *data, int x, int y, int color);
void	cleanup_scene(void *scene);

#endif
