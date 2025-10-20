/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:30:15 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/20 09:31:13 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# include "../lib/libft/include/libft.h"
# include "../lib/minilibx-linux/mlx.h"

/* ************************************************************************** */
/*                                   DEFINES                                  */
/* ************************************************************************** */

# define ESC_KEY 65307
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

/* ************************************************************************** */
/*                                 STRUCTURES                                 */
/* ************************************************************************** */

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

typedef struct	s_vector // vectors
{
    float	x;
    float	y;
    float	z;
}				t_vector;

typedef struct s_gd{ // general data, but also plane
    int	r;
    int	g;
    int	b;
    t_vector	v;
    float	nov_x; // nov = normalized orientation vector
    float	nov_y;
    float	nov_z;
} t_gd;

typedef struct	s_al{ //ambient light
    float	ratio;
    t_gd	colours;
} t_al;

typedef struct s_ray
{
    t_vector	origin;     // Starting point of the ray
    t_vector	direction;  // Direction vector (normalized)
}	t_ray;

typedef struct s_viewport
{
    int		width;        // Screen width in pixels
    int		height;       // Screen height in pixels
    float	aspect_ratio; // width/height ratio
}	t_viewport;

typedef struct s_camera
{
    t_vector	position;   // Camera position in world space
    t_vector	direction;  // Camera look-at direction (normalized)
    t_vector	up;         // Camera up direction (normalized)
    t_vector	right;      // Camera right direction (normalized)
    t_vector	forward;    // Camera forward direction (normalized)
    float		fov;        // Field of view in degrees
}	t_camera;

typedef struct s_l{	//light
    t_gd	coord;
    float	br;	// brightness ratio
} t_l;

typedef	struct s_sp { // sphere
    t_gd	coord_colours;
    float	d;	//diameter;
} t_sp;

typedef struct s_cy { // cylinder
    t_gd	data;
    float	d;
    float	h; // height
} t_cy;

typedef enum e_object_type {
    SPHERE,
    PLANE,
    CYLINDER
} t_object_type;

typedef struct s_objects { // linked list of objects
    t_object_type	type;
    void			*object; // FIXED: was object_data, now matches sphere.c usage
} t_objects;

typedef struct s_scene {
    t_al		ambient;		// Only one
    t_camera	cam;			// Only one
    t_l			light;			// Linked list (one for mandatory)
    t_list		*objects;		// FIXED: was objects_list, now matches sphere.c usage
} t_scene;

/* ************************************************************************** */
/*                             FUNCTION PROTOTYPES                            */
/* ************************************************************************** */

// event.c
int			exit_program(t_minirt *data);
int			keypress_handler(int key, t_minirt *data);
int			close_window(t_minirt *data);
void		init_event(t_minirt *data);

//main.c
int			init_minirt_basic(t_minirt *data);
void		render_test_scene(t_minirt *data);
void		put_pixel(t_minirt *data, int x, int y, int color);
void		cleanup_scene(void *scene);

// load_scene.c
size_t		lines_counting(char *filename);
t_scene		*creating_scene(int lines, char *filename);
t_scene		*load_scene(char *filename);

// parse_utils.c
void		skipping_emptiness(char **str);
float		ft_atof_dp(char **str);
int			ft_atoi_dp(char **str);

// main parsing functions
int			parsing_ambient(t_scene *sc1, char *line_data1);
int			parsing_camera(t_scene *sc2, char *line_data2);
int			parsing_light(t_scene *sc3, char *line_data3);
int			parsing_objects(t_scene *sc4, char *line_data4);

// xyz_extraction.c
void		extracting_xyz(t_scene *scene_coord, char **nums, char element);
void		extracting_nov_xyz(t_scene *scene_nov, char **novs, char element);

// object.c
bool		creating_object(t_scene *scene_o, t_object_type type_o, size_t size_o);

// sphere.c
int			parsing_sphere(t_scene *scene_sphere, char *ld4);

// vector_calc.c
t_vector	vector_add(t_vector a, t_vector b);
t_vector	vector_subtract(t_vector a, t_vector b);
t_vector	vector_scale(t_vector v, float s);
t_vector	vector_create(float x, float y, float z);

// vector_geom.c
float		vector_dot(t_vector a, t_vector b);
t_vector	vector_cross(t_vector a, t_vector b);
float		vector_length(t_vector v);
t_vector	vector_normalize(t_vector v);

// ray.c
t_ray		create_ray(t_vector origin, t_vector direction);
t_vector	ray_at(t_ray ray, float t);
t_ray		camera_ray(t_camera camera, int x, int y, t_viewport viewport);

// render_scene.c
void		render_scene(t_scene *scene, t_minirt *data);
t_gd		trace_ray(t_ray ray, t_scene *scene);
int			color_to_int(t_gd color);

//render_utils.c

#endif
