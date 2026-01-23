/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:10:01 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/09 06:51:23 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ========================== INCLUDES ========================== */

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* ========================== MACROS ========================== */

/* Window dimensions */
# define WIN_WIDTH  1280
# define WIN_HEIGHT 720
# define WIN_TITLE  "cub3D"

/* Texture indices */
# define TEX_NORTH	0
# define TEX_SOUTH	1
# define TEX_EAST	2
# define TEX_WEST	3

/* Key codes (Linux X11) */
# define KEY_ESC	65307
# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_LEFT	65361
# define KEY_RIGHT	65363

/* X11 Events */
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_DESTROY		17

/* Player settings */
# define MOVE_SPEED	0.05
# define ROT_SPEED	0.03

/* ========================== ENUMS ========================== */

typedef enum e_error
{
	ERR_NONE = 0,
	ERR_ARGS,
	ERR_FILE_EXT,
	ERR_FILE_OPEN,
	ERR_FILE_READ,
	ERR_MALLOC,
	ERR_MLX_INIT,
	ERR_MLX_WIN,
	ERR_MLX_IMG,
	ERR_TEX_PATH,
	ERR_TEX_LOAD,
	ERR_COLOR_FORMAT,
	ERR_COLOR_RANGE,
	ERR_MAP_CHAR,
	ERR_MAP_PLAYER,
	ERR_MAP_CLOSED,
	ERR_MAP_EMPTY,
	ERR_DUP_ELEMENT,
	ERR_MISS_ELEMENT
}	t_error;

/* ========================== STRUCTURES ========================== */

/* Texture / Image structure */
typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_tex;

/* Player structure */
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}	t_player;

/* Ray structure (for raycasting) */
typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
}	t_ray;

/* Map structure */
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

/* Parse state (temporary paths before MLX init) */
typedef struct s_parse
{
	char	*tex_paths[4];
	int		floor_set;
	int		ceiling_set;
	int		player_count;
	char	player_dir;
	int		player_x;
	int		player_y;
}	t_parse;

/* Main structure */
typedef struct s_cub3d
{
	void		*mlx;
	void		*win;
	t_tex		img;
	t_tex		tex[4];
	int			floor_color;
	int			ceiling_color;
	t_map		map;
	t_player	player;
	t_parse		parse;
	int			keys[256];
	int			key_left;
	int			key_right;
}	t_cub3d;

/* ========================== FUNCTION PROTOTYPES ========================== */

/* --- Core: error.c --- */
void		err_msg(t_error code);
void		err_exit(t_cub3d *cub, t_error code);

/* --- Core: cleanup.c --- */
void		cleanup(t_cub3d *cub);
void		free_array(char **arr);

/* --- Core: init.c --- */
void		init_cub(t_cub3d *cub);
void		init_mlx(t_cub3d *cub);
void		load_textures(t_cub3d *cub);

/* --- Core: init_player.c --- */
void		init_player(t_cub3d *cub);
void		init_player_direction(t_cub3d *cub);

/* --- Core: events.c --- */
void		setup_hooks(t_cub3d *cub);
int			close_window(t_cub3d *cub);

/* --- Core: keys.c --- */
int			key_press(int keycode, t_cub3d *cub);
int			key_release(int keycode, t_cub3d *cub);
void		process_input(t_cub3d *cub);

/* --- Parsing: parse_file.c --- */
void		parse_file(t_cub3d *cub, char *filename);

/* --- Parsing: parse_utils.c --- */
int			check_extension(char *filename, char *ext);
char		*trim_spaces(char *str);
int			is_empty_line(char *line);
void		remove_newline(char *line);

/* --- Parsing: parse_texture.c --- */
void		parse_texture(t_cub3d *cub, char *line, int tex_index);

/* --- Parsing: parse_colors.c --- */
void		parse_floor_color(t_cub3d *cub, char *line);
void		parse_ceiling_color(t_cub3d *cub, char *line);

/* --- Parsing: parse_rgb.c --- */
int			parse_rgb(t_cub3d *cub, char *str);

/* --- Parsing: parse_map.c --- */
void		add_map_line(t_cub3d *cub, char *line);
int			is_map_line(char *line);

/* --- Parsing: validate.c --- */
void		validate_map(t_cub3d *cub);
void		validate_elements(t_cub3d *cub);
void		extract_player(t_cub3d *cub);

/* --- Player: movement.c --- */
void		move_forward(t_cub3d *cub);
void		move_backward(t_cub3d *cub);
void		strafe_left(t_cub3d *cub);
void		strafe_right(t_cub3d *cub);

/* --- Player: rotation.c --- */
void		rotate_left(t_cub3d *cub);
void		rotate_right(t_cub3d *cub);

/* --- Raycasting: raycast.c --- */
void		raycast(t_cub3d *cub);
void		init_ray(t_cub3d *cub, t_ray *ray, int x);

/* --- Raycasting: dda.c --- */
void		calculate_step_and_side_dist(t_cub3d *cub, t_ray *ray);
void		perform_dda(t_cub3d *cub, t_ray *ray);

/* --- Raycasting: walls.c --- */
void		calculate_wall_height(t_ray *ray);

/* --- Raycasting: textures.c --- */
void		calculate_tex_x(t_cub3d *cub, t_ray *ray);
t_tex		*get_texture(t_cub3d *cub, t_ray *ray);
int			get_texture_color(t_tex *tex, int tex_x, int tex_y);

/* --- Render: render.c --- */
int			game_loop(t_cub3d *cub);

/* --- Render: draw.c --- */
void		put_pixel(t_tex *img, int x, int y, int color);
void		draw_floor_ceiling(t_cub3d *cub);
void		draw_column(t_cub3d *cub, t_ray *ray, int x);

/* --- Utils --- */
char		*trim_spaces(char *str);
int			is_empty_line(char *line);
void		remove_newline(char *line);

#endif