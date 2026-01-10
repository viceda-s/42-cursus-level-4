/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:30:15 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/06 14:01:19 by viceda-s         ###   ########.fr       */
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
# include <pthread.h>

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
# define KEY_Z 122

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
# define KEY_PAD_1 65436
# define KEY_PAD_2 65433
# define KEY_PAD_4 65430
# define KEY_PAD_6 65432
# define KEY_PAD_8 65431
# define KEY_PAD_9 65434
# define KEY_PAD_UP 65431 // Same as 8
# define KEY_PAD_DOWN 65433 // Same as 2
# define KEY_PAD_LEFT 65430 // Same as 4
# define KEY_PAD_RIGHT 65432 // Same as 6
# define KEY_PAD_UP 65431 // Same as 8
# define KEY_PAD_DOWN 65433 // Same as 2
# define KEY_PAD_LEFT 65430 // Same as 4
# define KEY_PAD_RIGHT 65432 // Same as 6

/* Render control keys */
# define KEY_F 102
# define KEY_H 104

/* speeds / constants */
# define MOVE_SPEED 5.0f
# define ROTATE_SPEED 0.1f
# define SHININESS 16.0f
# define ANTI_ALIASING_SAMPLES 9
# define NUM_THREADS 8

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

typedef struct s_rotation
{
	float	pitch;
	float	yaw;
	float	roll;
}				t_rotation;

/* UV mapping parameters */
typedef struct s_uv_params
{
	float	uv[2];
	float	half;
	float	abs_x;
	float	abs_y;
	float	abs_z;
}				t_uv_params;

/* texture data */
typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
	char	*filepath;
}				t_texture;

/* general data (used for color and plane) */
typedef struct s_gd
{
	int			r;
	int			g;
	int			b;
	bool		checker;
	/* optional procedural bump mapping parameters */
	bool		has_bump;
	float		bump_strength; /* default 1.0 */
	t_vector	bump_uv; /* scale for u,v (x,y) */
	t_vector	v; /* coordinate or origin */
	t_vector	nov; /* normalized orientation vector */
	/* texture mapping */
	t_texture	*texture;
	t_texture	*bump_map;
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
	t_texture	*texture;
	t_texture	*bump_map;
}				t_sp;

/* cylinder */
typedef struct s_cy
{
	t_gd		data;
	float		d;
	float		h; /* height */
	t_texture	*texture;
	t_texture	*bump_map;
}				t_cy;

typedef struct s_internal
{
	t_vector	*axis;
	t_vector	min_corner_bound;
	t_vector	max_corner_bound;
	float		t_min;
	float		t_max;
	float		origin;
	float		direction;
	float		min;
	float		max;
	float		t1;
	float		t2;
	int			hit_face;
}				t_internal;

typedef struct s_cu // cube
{
	t_gd			data;
	float			side;
	t_internal		param;
	t_texture		*texture;
	t_texture		*bump_map;
}				t_cu;

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
	CYLINDER,
	CUBE
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
	t_list			*lights_list; /* one required; may expand to list later */
	t_list			*objects_list; /* linked list of objects */
	t_objects		*selected_object; /* currently selected object */
	t_compulsory	checklist;
}				t_scene;

typedef struct s_aa_params
{
	t_scene		*scene;
	int			x;
	int			y;
	t_viewport	viewport;
}				t_aa_params;

typedef struct s_bump_params
{
	float		u;
	float		v;
	float		strength;
	t_vector	tbn[3];
}				t_bump_params;

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
	bool		show_help;
	bool		fast_render;
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
	float			distance;
	float			bump_intensity;
}				t_shade;

/* ------------------------
   Function prototypes
   (grouped by source file)
   ------------------------ */

/* Threading */
typedef struct s_thread_data
{
	int			id;
	int			start_y;
	int			end_y;
	t_minirt	*data;
}				t_thread_data;

void		*render_slice(void *arg);

/* event.c */
void		exit_program(t_minirt *data);
int			close_window(t_minirt *data);
void		init_event(t_minirt *data);
void		render_keys(t_minirt *data, int needs_render);

/* keys.c */
int			keypress_handler(int key, t_minirt *data);
int			keypress_handler2(int key, t_minirt *data, int needs_render);
int			keypress_handler3(int key, t_minirt *data, int needs_render);

/* light_control_bonus.c */
int			keypress_handler_lights(int key, t_minirt *data);

/* object_control_bonus.c */
int			keypress_handler_objects(int key, t_minirt *data);

/* camera_control.c */
t_vector	rotate_axis(t_vector v, float angle, int axis);
void		update_camera_vectors(t_camera *camera);
void		rotate_camera(t_camera *camera, float pitch, float yaw, float roll);
void		move_camera(t_camera *camera, t_vector direction, float distance);
void		moving_camera(t_camera *camera, float distance, char flag);

/* main_bonus.c */
int			init_minirt(t_minirt *data);
void		render_test_scene(t_minirt *data);
void		put_pixel(t_minirt *data, int x, int y, int color);
void		cleanup_scene(t_scene *scene);
void		cleanup_scene_textures(void *mlx, t_scene *scene);
void		cleanup_object_texture(void *mlx, t_objects *obj);

/* parsing / loading */
t_scene		*creating_scene(char *filename);
t_scene		*load_scene(char *file_path);
t_scene		*error_case(t_scene *scene_error, int fd_error,
				const char *l_error);
t_scene		*continuing_processing(char *line, t_scene *scn, int *fdesc);

/* parse utils */
void		skipping_emptiness(char **str);
void		skip_comma(char **str);
void		skip_texture(char **ptr);
char		*parse_texture_path(char **ptr);
char		*parse_bump_map_path(char **ptr);
void		parse_texture_map(char **ptr, t_texture **texture);
void		parse_bump_map(char **ptr, t_texture **bump_map);
float		ft_atof_dp(char **str);
int			ft_atoi_dp(char **str);

/* parsing main */
int			parsing_ambient(t_scene *sc1, char *line_data1);
int			parsing_camera(t_scene *sc2, char *line_data2);
int			parsing_light(t_scene *sc3, char *line_data3);
int			parsing_objects(t_scene *sc4, char *line_data4);
void		parse_checker(char **ptr, bool *checker);
void		parse_bump(char **ptr, bool *has, float *str, t_vector *uv);
void		parse_texture_sphere(char **ptr, t_sp *sp, void *mlx);
void		parse_texture_plane(char **ptr, t_gd *pl, void *mlx);
void		parse_texture_cylinder(char **ptr, t_cy *cy, void *mlx);
void		parse_texture_cube(char **ptr, t_cu *cu, void *mlx);
t_vector	parse_vector(char **ptr);
int			parse_color(char **ptr, t_gd *col);

/* objects */
bool		creating_object(t_scene *scene_o,
				t_object_type type_o, size_t size_o);
void		*getting_latest_object(t_scene *scene_o, t_object_type type_o);
void		free_object(void *obj);
void		free_light(void *light_content);

/* primitives parsing */
int			parsing_sphere(t_scene *scene_sphere, char *line_data_sphere);
int			parsing_plane(t_scene *scene_plane, char *line_data_plane);
int			parsing_cylinder(t_scene *scene_cylinder, char *line_data_cylinder);
int			parsing_cube(t_scene *scene_cube, char *line_data_cube);

/* rendering */
void		render_scene(t_scene *scene, t_minirt *data);
void		render_help_overlay(t_minirt *data);
t_gd		trace_ray(t_ray ray, t_scene *scene);
int			color_to_int(t_gd color);
t_gd		get_pixel_color_with_aa(t_scene *scene, int x, int y,
				t_viewport viewport);
t_gd		get_pixel_color_aa_quality(t_aa_params params, int samples);
void		stratified_sample(int i, int samples, float *x, float *y);
float		gaussian_weight(float x, float y, float cx, float cy);
void		map_plane_uv(t_vector p, t_gd *pl, float *u, float *v);
void		map_sphere_uv(t_vector p, t_sp *sp, float *u, float *v);
void		map_cylinder_uv(t_vector p, t_cy *cy, float *u, float *v);
void		map_cube_uv(t_vector p, t_cu *cube, float *u, float *v);

/* ray ops */
t_ray		create_ray(t_vector origin, t_vector direction);
t_vector	ray_at(t_ray ray, float t);
t_ray		camera_ray(t_camera camera, int x, int y, t_viewport viewport);
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
float		intersect_cube(t_ray ray, t_cu *cube);

/* intersection helpers */
float		find_closest_sphere_intersection(t_ray ray,
				t_scene *scene, t_sp **hit_sphere);
float		find_closest_plane_intersection(t_ray ray,
				t_scene *scene, t_gd **hit_plane);
float		find_closest_cylinder_intersection(t_ray ray,
				t_scene *scene, t_cy **hit_cylinder);
float		find_closest_cube_intersection(t_ray ray,
				t_scene *scene, t_cu **hit_cube);
float		find_closest_intersection(t_ray ray,
				t_scene *scene, void **hit_object, t_object_type *hit_type);

/* lighting */
t_gd		calculate_lighting(t_shade *s);
t_gd		apply_checkerboard(t_shade *s, float scale);
t_gd		apply_ambient_light(t_gd material_color, t_al ambient);
t_gd		apply_diffuse_light(t_gd color, t_l *light_data, t_l *params,
				float shadow_factor);
t_gd		apply_specular_light(t_gd colour, t_l *light_data, t_l *l_params,
				float shadow_factor);
t_gd		get_material_color_textured(t_shade *s);
float		compute_shadow_factor(t_vector hit_point, t_vector normal,
				t_scene *scene, t_l *current_light);

/* bump mapping */
void		build_tbn_from_normal(t_vector n, t_vector *t, t_vector *b);
float		fracf(float x);
float		height_fn(float u, float v);
t_vector	perturb_from_height(t_bump_params params, float *out_intensity);
t_vector	perturb_from_bump_map(t_texture *bump_map, t_bump_params params,
				float *out_intensity);
void		apply_bump_sphere(t_shade *s, float str_scale, float freq_scale);
void		apply_bump_plane(t_shade *s, float str_scale, float freq_scale);
void		apply_bump_cylinder(t_shade *s, float str_scale, float freq_scale);
void		apply_bump_cube(t_shade *s, float str_scale, float freq_scale);

/* normal utils */
t_vector	get_sphere_normal(void *object_data, t_vector hit_point);
t_vector	get_cylinder_normal(void *object_data, t_vector hit_point);
t_vector	get_cube_normal(void *ob_data, t_vector hit_pt);
t_vector	getting_normal_for_object(void *object_data,
				t_object_type type, t_vector hit_point);
t_gd		getting_material_color(void *object_data, t_object_type type);

/* transform_bonus.c */
void		translate_object(void *obj, t_object_type type, t_vector offset);
void		rotate_object(void *obj, t_object_type type, t_rotation rot);
void		translate_light(t_l *light, t_vector offset);

/* object_selection_bonus.c */
void		init_selection(t_scene *scene);
void		select_next_object(t_scene *scene);

/* texture_bonus.c */
t_texture	*load_texture(void *mlx, char *filepath);
t_gd		get_texture_color(t_texture *tex, float u, float v);
float		get_bump_height(t_texture *bump_map, float u, float v);
void		free_texture(void *mlx, t_texture *tex);
void		load_scene_textures(void *mlx, t_scene *scene);

#endif /* MINIRT_BONUS_H */
