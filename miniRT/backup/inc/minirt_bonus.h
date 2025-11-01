/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg.>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:44:09 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/31 20:05:29 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:30:15 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/31 15:54:06 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# include "../../lib/libft/include/libft.h"
# include "../../lib/minilibx-linux/mlx.h"

/* window / keys */
# define ESC_KEY 65307
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

/* Movement keys */
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Q 113
# define KEY_E 101

/* Arrow keys */
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

/* speeds / constants */
# define MOVE_SPEED 5.0f
# define ROTATE_SPEED 0.1f
# define SHININESS 32.0f
# define ANTI_ALIASING_SAMPLES 9

/* ------------------------
   Basic types / math data
   ------------------------ */

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}				t_vector;

typedef struct s_quadratic
{
	float	a;
	float	b;
	float	c;
	float	t1;
	float	t2;
}	t_quadratic;

/* general data (used for color and plane) */
typedef struct s_gd
{
	int			r;
	int			g;
	int			b;
	bool		checker;
	t_vector	v; /* coordinate or origin */
	t_vector	nov; /* normalized orientation vector */
}				t_gd;

/* ambient light */
typedef struct s_al
{
	float	ratio;
	t_gd	colours;
}				t_al;

/* light parameters */
typedef struct s_l
{
	t_gd				coord;
	t_gd				material_color;
	struct s_scene		*scene;
	t_vector			normal;
	t_vector			light_dir;
	float				br; /* brightness ratio */
	t_vector			view_dir;
}				t_l;

/* sphere */
typedef struct s_sp
{
	t_gd		coord_colours;
	float		d; /* diameter */
}				t_sp;

/* cylinder */
typedef struct s_cy
{
	t_gd	data;
	float	d;
	float	h; /* height */
}				t_cy;

/* ray / camera / viewport */
typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}				t_ray;

typedef struct s_camera
{
	t_vector	position;
	t_vector	forward; /* z axis */
	t_vector	up; /* y axis */
	t_vector	right; /* x axis */
	int			fov;
}				t_camera;

typedef struct s_viewport
{
	int		width;
	int		height;
	float	aspect_ratio;
}				t_viewport;

/* ------------------------
   Object types & lists
   ------------------------ */

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER
}				t_object_type;

typedef struct s_objects
{
	t_object_type	type;
	void			*object_data; /* points to t_sp / t_gd (plane) / t_cy */
}				t_objects;

/* ------------------------
   Scene / hits / runtime
   ------------------------ */

typedef struct s_compulsory
{
	size_t	ambient_set;
	size_t	camera_set;
	size_t	light_set;
}				t_compulsory;

typedef struct s_scene
{
	t_al			ambient; /* only one */
	t_camera		camera; /* only one */
	t_l				light; /* one required; may expand to list later */
	t_list			*objects_list; /* linked list of objects */
	t_compulsory	checklist;
}				t_scene;

typedef struct s_hit
{
	float			closest_t;
	void			**hit_object;
	t_object_type	*hit_type;
}				t_hit;

typedef struct s_minirt
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			win_height;
	int			win_width;
	t_scene		*scene;
}				t_minirt;

typedef struct s_shade
{
	t_vector		hit_point;
	t_vector		normal;
	t_vector		view_dir;
	t_gd			material_color;
	t_scene			*scene;
	void			*hit_object;
	t_object_type	hit_type;
}				t_shade;

/* ------------------------
   Function prototypes
   (grouped by source file)
   ------------------------ */

/* event.c */
void		exit_program(t_minirt *data);
int			close_window(t_minirt *data);
void		init_event(t_minirt *data);

/* keys.c */
int			keypress_handler(int key, t_minirt *data);
int			keypress_handler2(int key, t_minirt *data, int needs_render);
int			keypress_handler3(int key, t_minirt *data, int needs_render);

/* camera_control.c */
t_vector	rotate_axis(t_vector v, float angle, int axis);
void		update_camera_vectors(t_camera *camera);
void		rotate_camera(t_camera *camera, float pitch, float yaw, float roll);
void		move_camera(t_camera *camera, t_vector direction, float distance);
void		moving_camera(t_camera *camera, float distance, char flag);

/* main_bonus.c */
int			init_minirt_basic(t_minirt *data);
void		render_test_scene(t_minirt *data);
void		put_pixel(t_minirt *data, int x, int y, int color);
void		cleanup_scene(t_scene *scene);

/* parsing / loading */
t_scene		*creating_scene(char *filename);
t_scene		*load_scene(char *file_path);

/* parse utils */
void		skipping_emptiness(char **str);
void		skip_comma(char **str);
float		ft_atof_dp(char **str);
int			ft_atoi_dp(char **str);

/* parsing main */
int			parsing_ambient(t_scene *sc1, char *line_data1);
int			parsing_camera(t_scene *sc2, char *line_data2);
int			parsing_light(t_scene *sc3, char *line_data3);
int			parsing_objects(t_scene *sc4, char *line_data4);
void		parse_checker_plane(char **ptr, t_gd *gd);
void		parse_checker_sphere(char **ptr, t_sp *sp);
void		parse_checker_cylinder(char **ptr, t_cy *cy);
t_vector	parse_vector(char **ptr);
void		parse_color(char **ptr, t_gd *col);

/* extraction helpers */
void		extracting_xyz(t_scene *scene_coord, char **nums, char element);
void		extracting_nov_cam(t_scene *scene_nov, char **novs);

/* objects */
bool		creating_object(t_scene *scene_o,
				t_object_type type_o, size_t size_o);
void		*getting_latest_object(t_scene *scene_o, t_object_type type_o);
void		free_object(void *obj);

/* primitives parsing */
int			parsing_sphere(t_scene *scene_sphere, char *line_data_sphere);
int			parsing_plane(t_scene *scene_plane, char *line_data_plane);
int			parsing_cylinder(t_scene *scene_cylinder, char *line_data_cylinder);

/* rendering */
void		render_scene(t_scene *scene, t_minirt *data);
t_gd		trace_ray(t_ray ray, t_scene *scene);
int			color_to_int(t_gd color);
t_gd		get_pixel_color_with_aa(t_scene *scene, int x, int y,
				t_viewport viewport);

/* ray ops */
t_ray		create_ray(t_vector origin, t_vector direction);
t_vector	ray_at(t_ray ray, float t);
t_ray		camera_ray(t_camera camera, int x, int y, t_viewport viewport);

/* vector ops */
t_vector	vector_create(float x, float y, float z);
t_vector	vector_add(t_vector a, t_vector b);
t_vector	vector_sub(t_vector a, t_vector b);
t_vector	vector_scale(t_vector v, float s);

/* vector geometry */
float		vector_dot(t_vector a, t_vector b);
t_vector	vector_cross(t_vector a, t_vector b);
float		vector_length(t_vector v);
t_vector	vector_normalize(t_vector v);

/* intersections */
float		intersect_sphere(t_ray ray, t_sp *sphere);
float		intersect_plane(t_ray ray, t_gd *plane);
float		intersect_cylinder(t_ray ray, t_cy *cylinder);

/* intersection helpers */
float		find_closest_sphere_intersection(t_ray ray,
				t_scene *scene, t_sp **hit_sphere);
float		find_closest_plane_intersection(t_ray ray,
				t_scene *scene, t_gd **hit_plane);
float		find_closest_cylinder_intersection(t_ray ray,
				t_scene *scene, t_cy **hit_cylinder);
float		find_closest_intersection(t_ray ray,
				t_scene *scene, void **hit_object, t_object_type *hit_type);

/* lighting */
t_gd		calculate_lighting(t_shade *s);
t_gd		apply_checkerboard(t_vector p, t_gd c1, float scale,
				void *object, t_object_type type);

#endif /* MINIRT_BONUS_H */
