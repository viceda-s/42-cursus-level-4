/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg.>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:25:48 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/04 14:43:06 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:30:15 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/27 20:03:07 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <math.h>

# include "../../lib/libft/include/libft.h"
# include "../../lib/minilibx-linux/mlx.h"

# define ESC_KEY 65307
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

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

/* Light movement keys */
# define KEY_I 105
# define KEY_J 106
# define KEY_K 107
# define KEY_L 108
# define KEY_U 117
# define KEY_O 111

/* Object control keys (Numpad) */
# define KEY_TAB 65289
# define KEY_PAD_2 65433
# define KEY_PAD_4 65430
# define KEY_PAD_6 65432
# define KEY_PAD_8 65431
# define KEY_PAD_7 65429
# define KEY_PAD_9 65434
# define KEY_PAD_UP 65431 // Same as 8
# define KEY_PAD_DOWN 65433 // Same as 2
# define KEY_PAD_LEFT 65430 // Same as 4
# define KEY_PAD_RIGHT 65432 // Same as 6

// Movement and rotation speed
# define MOVE_SPEED 5.0f
# define ROTATE_SPEED 0.1f

typedef struct s_quadratic // equacao quadratica e formula de bhaskara
{
	float	a;
	float	b;
	float	c;
	float	t1;
	float	t2;
}	t_quadratic;

typedef struct s_rotation
{
	float	pitch;
	float	yaw;
	float	roll;
}				t_rotation;

typedef struct s_vector // vectors
{
	float	x;
	float	y;
	float	z;
}				t_vector;

typedef struct s_gd // general data, but also plane
{
	int			r;
	int			g;
	int			b;
	t_vector	v;
	t_vector	nov; // nov = normalized orientation vector
}				t_gd;

typedef struct s_al //ambient light
{
	float	ratio;
	t_gd	colours;
}				t_al;

typedef struct s_l //light
{
	t_vector			position;
	t_gd				coord;
	t_gd				material_color;
	struct s_scene		*scene;
	t_vector			normal;
	t_vector			light_dir;
	float				br;	// brightness ratio
}				t_l;

typedef struct s_sp // sphere
{
	t_gd		coord_colours;
	float		d; //diameter;
}				t_sp;

typedef struct s_cy // cylinder
{
	t_gd	data;
	float	d;
	float	h; // height
}				t_cy;

// Ray structures for raytracing
typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}				t_ray;

typedef struct s_camera
{
	t_vector	position;
	t_vector	forward; // z axis
	t_vector	up; // y axis
	t_vector	right; // x axis
	int			fov;
}				t_camera;

typedef struct s_viewport
{
	int		width;
	int		height;
	float	aspect_ratio;
}				t_viewport;

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER
}			t_object_type;

typedef struct s_objects // linked list of objects
{
	t_object_type	type;
	void			*object_data; // *data like t_sp, t_pl or t_cy
}				t_objects;

typedef struct s_compulsory
{
	size_t	ambient_set;
	size_t	camera_set;
	size_t	light_set;
}				t_compulsory;

typedef struct s_scene
{
	t_al			ambient; // Only one
	t_camera		camera; // Only one
	t_l				light; // Linked list (one for mandatory)
	t_list			*objects_list; // Linked list (spheres, planes, cylinders)
	t_objects		*selected_object; /* currently selected object */
	t_compulsory	checklist;
}				t_scene;

typedef struct s_hit // closest ray-object intersection
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

// event.c
void		exit_program(t_minirt *data);
int			close_window(t_minirt *data);
void		init_event(t_minirt *data);

// keys.c
int			keypress_handler(int key, t_minirt *data);
int			keypress_handler2(int key, t_minirt *data, int needs_render);
int			keypress_handler3(int key, t_minirt *data, int needs_render);

/* light_control.c */
int			keypress_handler_lights(int key, t_minirt *data);

/* object_control.c */
int			keypress_handler_objects(int key, t_minirt *data);

/* object_selection.c */
void		init_selection(t_scene *scene);
void		select_next_object(t_scene *scene);

/* camera_control.c */
t_vector	rotate_axis(t_vector v, float angle, int axis);
void		update_camera_vectors(t_camera *camera);
void		rotate_camera(t_camera *camera, float pitch, float yaw, float roll);
void		move_camera(t_camera *camera, t_vector direction, float distance);
void		moving_camera(t_camera *camera, float distance, char flag);

//main.c
int			init_minirt(t_minirt *data);
void		render_test_scene(t_minirt *data);
void		put_pixel(t_minirt *data, int x, int y, int color);
void		cleanup_scene(t_scene *scene);

// parsing/load_scene.c
t_scene		*creating_scene(char *filename);
t_scene		*load_scene(char *file_path);

// parse_utils.c
void		skipping_emptiness(char **str);
void		skip_comma(char **str);
float		ft_atof_dp(char **str);
int			ft_atoi_dp(char **str);

// main parsing functions (from parsing.c)
int			parsing_ambient(t_scene *sc1, char *line_data1);
int			parsing_camera(t_scene *sc2, char *line_data2);
int			parsing_light(t_scene *sc3, char *line_data3);
int			parsing_objects(t_scene *sc4, char *line_data4);
t_scene		*parse_scene(char *filename);

// parse_helper.c
t_vector	parse_vector(char **ptr);
int			parse_color(char **ptr, t_gd *col);

// object.c
bool		creating_object(t_scene *scene_o, t_object_type type_o,
				size_t size_o);
void		*getting_latest_object(t_scene *scene_o, t_object_type type_o);
void		free_object(void *obj);

// sphere.c
int			parsing_sphere(t_scene *scene_sphere, char *line_data_sphere);

// plane.c
int			parsing_plane(t_scene *scene_plane, char *line_data_plane);

// cylinder.c
int			parsing_cylinder(t_scene *scene_cylinder, char *line_data_cylinder);

// transform.c
void		translate_object(void *obj, t_object_type type, t_vector offset);
void		rotate_object(void *obj, t_object_type type, t_rotation rot);
void		translate_light(t_l *light, t_vector offset);

// render_scene.c
void		render_scene(t_scene *scene, t_minirt *data);
t_gd		trace_ray(t_ray ray, t_scene *scene);
int			color_to_int(t_gd color);

// ray_ops.c
t_ray		create_ray(t_vector origin, t_vector direction);
t_vector	ray_at(t_ray ray, float t);
t_ray		camera_ray(t_camera camera, int x, int y, t_viewport viewport);

// vector_ops.c
t_vector	vector_create(float x, float y, float z);
t_vector	vector_add(t_vector a, t_vector b);
t_vector	vector_sub(t_vector a, t_vector b);
t_vector	vector_scale(t_vector v, float s);

// vector_geo.c
float		vector_dot(t_vector a, t_vector b);
t_vector	vector_cross(t_vector a, t_vector b);
float		vector_length(t_vector v);
t_vector	vector_normalize(t_vector v);

// intersections.c
float		intersect_sphere(t_ray ray, t_sp *sphere);
float		intersect_plane(t_ray ray, t_gd *plane);
float		intersect_cylinder(t_ray ray, t_cy *cylinder);

// intersect_utils.c
float		find_closest_sphere_intersection(t_ray ray, t_scene *scene,
				t_sp **hit_sphere);
float		find_closest_plane_intersection(t_ray ray, t_scene *scene,
				t_gd **hit_plane);
float		find_closest_cylinder_intersection(t_ray ray, t_scene *scene,
				t_cy **hit_cylinder);
float		find_closest_intersection(t_ray ray, t_scene *scene,
				void **hit_object, t_object_type *hit_type);

// lighting.c
t_gd		calculate_lighting(t_vector hpoint, t_vector normal,
				t_scene *scene, t_gd material_color);

#endif
