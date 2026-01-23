/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:16:15 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 14:35:53 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

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
# define WIN_TITLE  "cub3D (Bonus edition)"

/* Texture indices */
# define TEX_NORTH	0
# define TEX_SOUTH	1
# define TEX_EAST	2
# define TEX_WEST	3
# define TEX_DOOR_START	4
# define TEX_COUNT	13

/* Key codes (Linux X11) */
# define KEY_ESC	65307
# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_E		101
# define KEY_LEFT	65361
# define KEY_RIGHT	65363

/* X11 Events */
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_MOUSE_PRESS	4
# define X_EVENT_MOUSE_MOVE		6
# define X_EVENT_DESTROY		17

/* Mouse buttons */
# define MOUSE_LEFT		1
# define MOUSE_RIGHT		3

/* Player settings */
# define MOVE_SPEED		0.05
# define ROT_SPEED		0.03
# define MOUSE_SENS		0.002

/* Target settings */
# define TARGET_ACTIVE	0
# define TARGET_HIT		1

/* Target animation */
# define TARGET_FRAMES	1
# define TARGET_SPRITES	2

/* Minimap settings */
# define MINIMAP_SCALE	8
# define MINIMAP_SIZE	150
# define MINIMAP_X		20
# define MINIMAP_Y		20

/* Minimap colors */
# define MM_WALL		0x333333
# define MM_FLOOR		0x666666
# define MM_PLAYER		0x00FF00
# define MM_DOOR		0xFFAA00
# define MM_DOOR_OPEN	0x00FFFF
# define MM_BG			0x000000

/* Transparency */
# define TRANSPARENT_COLOR	0xFF00FF

/* Door states */
# define DOOR_CLOSED	0
# define DOOR_OPEN	1
# define DOOR_OPENING	2
# define DOOR_CLOSING	3

/* Door animation */
# define DOOR_FRAMES		9
# define DOOR_FRAME_TIME	2

/* Weapon animation */
# define WEAPON_IDLE_FRAMES		1
# define WEAPON_WALK_FRAMES		2
# define WEAPON_FIRE_FRAMES		5
# define WEAPON_TOTAL_FRAMES	8
# define WEAPON_IDLE_TICK		8
# define WEAPON_WALK_TICK		8
# define WEAPON_FIRE_TICK		3

/* Weapon bob (CS-style smooth walk) */
# define BOB_SPEED				0.15
# define BOB_AMOUNT_X			8.0
# define BOB_AMOUNT_Y			6.0

/* ========================== ENUMS ========================== */

typedef enum e_error_bonus
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

/* Door structure */
typedef struct s_door
{
	int		x;
	int		y;
	int		state;
	int		anim_frame;
	int		anim_timer;
}	t_door;

/* Weapon structure */
typedef struct s_weapon
{
	t_tex	sprites[WEAPON_TOTAL_FRAMES];
	int		is_shooting;
	int		is_walking;
	int		current_frame;
	int		tick_count;
	double	bob_time;
	int		bob_x;
	int		bob_y;
}	t_weapon;

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

/* Target structure */
typedef struct s_target
{
	double	pos_x;
	double	pos_y;
	int		state;
	int		sprite_index;
	double	distance;
}	t_target;

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
	int		hit_door;
	int		door_map_x;
	int		door_map_y;
	double	door_perp_dist;
	int		door_side;
	int		has_wall_behind;
	int		wall_map_x;
	int		wall_map_y;
	double	wall_perp_dist;
	int		wall_side;
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
	char	*tex_paths[TEX_COUNT];
	int		floor_set;
	int		ceiling_set;
	int		player_count;
	char	player_dir;
	int		player_x;
	int		player_y;
}	t_parse;

/* Sprite structure (for rendering) */
typedef struct s_sprite
{
	double	x;
	double	y;
	int		tex;
	double	distance;
}	t_sprite;

/* Main structure */
typedef struct s_cub3d
{
	void		*mlx;
	void		*win;
	t_tex		img;
	t_tex		tex[TEX_COUNT];
	int			floor_color;
	int			ceiling_color;
	t_map		map;
	t_player	player;
	t_parse		parse;
	int			keys[256];
	int			key_left;
	int			key_right;
	t_door		*doors;
	int			door_count;
	int			mouse_enabled;
	int			last_mouse_x;
	t_weapon	weapon;
	t_target	*targets;
	int			target_count;
	int			score;
	t_tex		target_tex[2];
	t_sprite	*sprites;
	int			sprite_count;
	double		z_buffer[WIN_WIDTH];
}	t_cub3d;

/* ========================== FUNCTION PROTOTYPES ========================== */

/* --- Core: error_bonus.c --- */
void		err_msg(t_error code);
void		err_exit(t_cub3d *cub, t_error code);

/* --- Core: cleanup_bonus.c --- */
void		cleanup(t_cub3d *cub);
void		free_array(char **arr);

/* --- Core: cleanup_utils_bonus.c --- */
void		cleanup_target_textures(t_cub3d *cub);
void		cleanup_weapon(t_cub3d *cub);
void		cleanup_game_objects(t_cub3d *cub);

/* --- Core: init_bonus.c --- */
void		init_cub(t_cub3d *cub);
void		init_mlx(t_cub3d *cub);
void		load_textures(t_cub3d *cub);

/* --- Core: init_player_bonus.c --- */
void		init_player(t_cub3d *cub);
void		init_player_direction(t_cub3d *cub);

/* --- Core: events_bonus.c --- */
void		setup_hooks(t_cub3d *cub);
int			close_window(t_cub3d *cub);

/* --- Core: keys_bonus.c --- */
int			key_press(int keycode, t_cub3d *cub);
int			key_release(int keycode, t_cub3d *cub);
void		process_input(t_cub3d *cub);

/* --- Parsing: parse_file_bonus.c --- */
void		parse_file(t_cub3d *cub, char *filename);

/* --- Parsing: parse_utils_bonus.c --- */
int			check_extension(char *filename, char *ext);
char		*trim_spaces(char *str);
int			is_empty_line(char *line);
void		remove_newline(char *line);

/* --- Parsing: parse_texture_bonus.c --- */
void		parse_texture(t_cub3d *cub, char *line, int tex_index);

/* --- Parsing: parse_colors_bonus.c --- */
void		parse_floor_color(t_cub3d *cub, char *line);
void		parse_ceiling_color(t_cub3d *cub, char *line);

/* --- Parsing: parse_rgb_bonus.c --- */
int			parse_rgb(t_cub3d *cub, char *str);

/* --- Parsing: parse_map_bonus.c --- */
void		add_map_line(t_cub3d *cub, char *line);
int			is_map_line(char *line);

/* --- Parsing: validate_bonus.c --- */
void		validate_map(t_cub3d *cub);
void		validate_elements(t_cub3d *cub);
void		extract_player(t_cub3d *cub);

/* --- Player: movement_bonus.c --- */
void		move_forward(t_cub3d *cub);
void		move_backward(t_cub3d *cub);
void		strafe_left(t_cub3d *cub);
void		strafe_right(t_cub3d *cub);

/* --- Player: rotation_bonus.c --- */
void		rotate_left(t_cub3d *cub);
void		rotate_right(t_cub3d *cub);

/* --- Raycasting: raycast_bonus.c --- */
void		raycast(t_cub3d *cub);
void		init_ray(t_cub3d *cub, t_ray *ray, int x);

/* --- Raycasting: dda_bonus.c --- */
void		calculate_step_and_side_dist(t_cub3d *cub, t_ray *ray);
void		perform_dda(t_cub3d *cub, t_ray *ray);

/* --- Raycasting: dda_utils_bonus.c --- */
int			handle_door_hit(t_cub3d *cub, t_ray *ray);
void		save_wall_behind_info(t_cub3d *cub, t_ray *ray);

/* --- Raycasting: walls_bonus.c --- */
void		calculate_wall_height(t_ray *ray);

/* --- Raycasting: textures_bonus.c --- */
void		calculate_tex_x(t_cub3d *cub, t_ray *ray);
t_tex		*get_texture(t_cub3d *cub, t_ray *ray);
int			get_texture_color(t_tex *tex, int tex_x, int tex_y);

/* --- Render: render_bonus.c --- */
int			game_loop(t_cub3d *cub);

/* --- Render: draw_bonus.c --- */
void		put_pixel(t_tex *img, int x, int y, int color);
void		draw_floor_ceiling(t_cub3d *cub);
void		draw_column(t_cub3d *cub, t_ray *ray, int x);

/* --- Render: draw_utils_bonus.c --- */
void		calc_wall_params(t_ray *ray, double perp_dist, int *params);
double		calc_wall_x(t_cub3d *cub, t_ray *ray, double perp_dist);
int			calc_tex_x(t_cub3d *cub, t_ray *ray, t_tex *tex, double wall_x);
void		draw_tex_column(t_cub3d *cub, t_tex *tex, int *p, int x);

/* --- Bonus: minimap_bonus.c --- */
void		draw_minimap(t_cub3d *cub);

/* --- Bonus: mouse_bonus.c --- */
int			mouse_move(int x, int y, t_cub3d *cub);
int			mouse_press(int button, int x, int y, t_cub3d *cub);

/* --- Bonus: doors_bonus.c --- */
void		init_doors(t_cub3d *cub);
void		toggle_door(t_cub3d *cub);
void		update_doors(t_cub3d *cub);
int			is_door(t_cub3d *cub, int x, int y);
int			is_door_open(t_cub3d *cub, int x, int y);

/* --- Bonus: collision_bonus.c --- */
int			is_wall_bonus(t_cub3d *cub, double x, double y);

/* --- Bonus: weapon_bonus.c --- */
void		init_weapon(t_cub3d *cub);
void		load_weapon_sprite(t_cub3d *cub);
void		shoot_weapon(t_cub3d *cub);
void		update_weapon(t_cub3d *cub);
void		draw_weapon(t_cub3d *cub);

/* --- Bonus: target_bonus.c --- */
void		init_targets(t_cub3d *cub);
void		count_targets(t_cub3d *cub);
void		load_target_textures(t_cub3d *cub);
int			get_target_sprite_index(t_target *target);

/* --- Bonus: sprite_render_bonus.c --- */
void		prepare_sprites(t_cub3d *cub);
void		sort_sprites(t_sprite *sprites, int count);
void		render_sprites(t_cub3d *cub, double *z_buffer);
void		draw_sprite(t_cub3d *cub, t_sprite *sprite, double *z_buffer);

/* --- Bonus: target_hit_bonus.c --- */
void		check_target_hit(t_cub3d *cub);
void		draw_score(t_cub3d *cub);

#endif