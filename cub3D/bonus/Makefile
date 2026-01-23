# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::   #
#    Makefile                                           :+:      :+:    :+:   #
#                                                     +:+ +:+         +:+     #
#    By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2025/12/02 17:20:00 by viceda-s          #+#    #+#             #
#    Updated: 2025/12/02 17:20:00 by viceda-s         ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

# ================================ VARIABLES ================================ #

NAME		= ../cub3D_bonus
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I../inc -I../lib/libft/include -I../lib/minilibx-linux

# Libraries
LIBFT_DIR	= ../lib/libft
LIBFT		= $(LIBFT_DIR)/libft.a
MLX_DIR		= ../lib/minilibx-linux
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Colors
GREEN		= \033[0;32m
BLUE		= \033[0;34m
NC			= \033[0m

# Source files
SRCS		= src_bonus/main_bonus.c \
			  src_bonus/core/cleanup_bonus.c \
			  src_bonus/core/error_bonus.c \
			  src_bonus/core/events_bonus.c \
			  src_bonus/core/init_bonus.c \
			  src_bonus/core/init_player_bonus.c \
			  src_bonus/core/keys_bonus.c \
			  src_bonus/core/load_textures_bonus.c \
			  src_bonus/parsing/parse_colors_bonus.c \
			  src_bonus/parsing/parse_file_bonus.c \
			  src_bonus/parsing/parse_map_bonus.c \
			  src_bonus/parsing/parse_rgb_bonus.c \
			  src_bonus/parsing/parse_texture_bonus.c \
			  src_bonus/parsing/parse_utils_bonus.c \
			  src_bonus/parsing/validate_bonus.c \
			  src_bonus/player/movement_bonus.c \
			  src_bonus/player/rotation_bonus.c \
			  src_bonus/raycasting/dda_bonus.c \
			  src_bonus/raycasting/raycast_bonus.c \
			  src_bonus/raycasting/textures_bonus.c \
			  src_bonus/raycasting/walls_bonus.c \
			  src_bonus/render/draw_bonus.c \
			  src_bonus/render/render_bonus.c \
			  src_bonus/minimap_bonus.c \
			  src_bonus/mouse_bonus.c \
			  src_bonus/doors_bonus.c \
			  src_bonus/collision_bonus.c \
			  src_bonus/weapon_bonus.c \
			  src_bonus/enemy_bonus.c \
			  src_bonus/enemy_ai_bonus.c \
			  src_bonus/enemy_hit_bonus.c \
			  src_bonus/sprite_render_bonus.c

OBJS_DIR	= obj_bonus
OBJS		= $(SRCS:src_bonus/%.c=$(OBJS_DIR)/%.o)

# ================================== RULES ================================== #

all: $(LIBFT) $(NAME)
	@echo "$(GREEN)cub3D_bonus compiled successfully!$(NC)"

$(NAME): $(OBJS)
	@echo "$(BLUE)Linking cub3D_bonus...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@chmod +x $(NAME)

$(OBJS_DIR)/%.o: src_bonus/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -C $(LIBFT_DIR) --silent

clean:
	@echo "Cleaning bonus object files..."
	@rm -rf $(OBJS_DIR)
	@echo "[OK] Bonus object files removed!"

fclean: clean
	@rm -f $(NAME)
	@echo "[OK] Bonus binary removed!"

re: fclean all

.PHONY: all clean fclean re
