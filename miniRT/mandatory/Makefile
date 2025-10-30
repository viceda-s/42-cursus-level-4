# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/13 12:34:14 by viceda-s          #+#    #+#              #
#    Updated: 2025/10/28 08:28:39 by viceda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

# Directories
SRC_DIR = src
INC_DIR = inc
LIB_DIR = ../lib
OBJ_DIR = obj

# Libraries
LIBFT_DIR = $(LIB_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = $(LIB_DIR)/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

# Source files
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/core/event.c \
       $(SRC_DIR)/core/keys.c \
       $(SRC_DIR)/core/camera_control.c \
       $(SRC_DIR)/parsing/parsing.c \
       $(SRC_DIR)/parsing/parse_utils.c \
       $(SRC_DIR)/parsing/load_scene.c \
       $(SRC_DIR)/parsing/xyz_extraction.c \
       $(SRC_DIR)/objects/object.c \
       $(SRC_DIR)/objects/sphere.c \
       $(SRC_DIR)/objects/cylinder.c \
       $(SRC_DIR)/objects/plane.c \
       $(SRC_DIR)/math/vector/vector_ops.c \
       $(SRC_DIR)/math/vector/vector_geo.c \
       $(SRC_DIR)/math/ray/ray_ops.c \
       $(SRC_DIR)/math/render/render_scene.c \
       $(SRC_DIR)/math/render/render_utils.c \
       $(SRC_DIR)/math/intersect/intersect.c \
       $(SRC_DIR)/math/intersect/intersect_check.c \
       $(SRC_DIR)/math/intersect/intersect_utils.c

# Object files
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fPIC
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)/include -I$(MLX_DIR)
LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
NC = \033[0m # No Color

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) compiled successfully!$(NC)"

# Create object directory structure
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/$(SRC_DIR)/core
	@mkdir -p $(OBJ_DIR)/$(SRC_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/$(SRC_DIR)/objects
	@mkdir -p $(OBJ_DIR)/$(SRC_DIR)/math/vector
	@mkdir -p $(OBJ_DIR)/$(SRC_DIR)/math/ray
	@mkdir -p $(OBJ_DIR)/$(SRC_DIR)/math/render
	@mkdir -p $(OBJ_DIR)/$(SRC_DIR)/math/intersect

# Compile object files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build libft
$(LIBFT):
	@echo "$(YELLOW)Building libft...$(NC)"
	@make -C $(LIBFT_DIR)

# Build MLX
$(MLX):
	@echo "$(YELLOW)Building MLX...$(NC)"
	@make -C $(MLX_DIR)

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean

# Clean everything
fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(NC)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

# Bonus (not implemented yet)
bonus: all

.PHONY: all clean fclean re bonus
