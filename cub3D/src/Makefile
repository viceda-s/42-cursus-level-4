# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/02 12:30:00 by viceda-s          #+#    #+#              #
#    Updated: 2025/12/02 16:33:13 by viceda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../cub3D

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Directories
INC_DIR = ../inc
LIB_DIR = ../lib
LIBFT_DIR = $(LIB_DIR)/libft
MLX_DIR = $(LIB_DIR)/minilibx-linux

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

# MLX Flags
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm

# Source files
SRCS = main.c \
	core/cleanup.c \
	core/error.c \
	core/events.c \
	core/init.c \
	core/init_player.c \
	core/keys.c \
	core/load_textures.c \
	parsing/parse_colors.c \
	parsing/parse_file.c \
	parsing/parse_map.c \
	parsing/parse_rgb.c \
	parsing/parse_texture.c \
	parsing/parse_utils.c \
	parsing/validate.c \
	player/movement.c \
	player/rotation.c \
	raycasting/dda.c \
	raycasting/raycast.c \
	raycasting/textures.c \
	raycasting/walls.c \
	render/draw.c \
	render/render.c

# Object files
OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
NC = \033[0m

all: $(LIBFT) $(MLX) $(NAME)
	@echo "$(GREEN)cub3D compiled successfully!$(NC)"

$(NAME): $(OBJS)
	@echo "$(BLUE)Linking cub3D...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@chmod +x $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/include -I$(MLX_DIR) -c $< -o $@

$(LIBFT):
	@echo "$(BLUE)Building libft...$(NC)"
	@$(MAKE) -s -C $(LIBFT_DIR)

$(MLX):
	@echo "$(BLUE)Building minilibx...$(NC)"
	@$(MAKE) -s -C $(MLX_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)Object files cleaned.$(NC)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "$(YELLOW)Binary cleaned.$(NC)"

re: fclean all

.PHONY: all clean fclean re
