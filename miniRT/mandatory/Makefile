# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/13 12:34:14 by viceda-s          #+#    #+#              #
#    Updated: 2025/10/28 15:44:30 by viceda-s         ###   ########.fr        #
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
       $(SRC_DIR)/core/camera_control.c \
       $(SRC_DIR)/core/event.c \
       $(SRC_DIR)/core/keys.c \
       $(SRC_DIR)/core/light_control.c \
       $(SRC_DIR)/core/object_control.c \
       $(SRC_DIR)/core/object_selection.c \
       $(SRC_DIR)/parsing/parsing.c \
       $(SRC_DIR)/parsing/parse_utils.c \
       $(SRC_DIR)/parsing/load_scene.c \
       $(SRC_DIR)/parsing/parse_helper.c \
       $(SRC_DIR)/objects/object.c \
       $(SRC_DIR)/objects/sphere.c \
       $(SRC_DIR)/objects/cylinder.c \
       $(SRC_DIR)/objects/plane.c \
       $(SRC_DIR)/objects/transform.c \
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
GREEN_BOLD = \033[1;32m
RED = \033[0;31m
RED_BOLD = \033[1;31m
YELLOW = \033[0;33m
YELLOW_BOLD = \033[1;33m
NC = \033[0m # No Color

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN_BOLD)✅ $(NAME) compiled successfully!$(NC)"

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
	@make -s -C $(LIBFT_DIR) --no-print-directory > /dev/null
	@echo "$(GREEN_BOLD)✅ libft compiled!$(NC)"

# Build MLX
$(MLX):
	@echo "$(YELLOW)Building MiniLibX...$(NC)"
	@make -s -C $(MLX_DIR) --no-print-directory > /dev/null
	@echo "$(GREEN_BOLD)✅ MiniLibX compiled!$(NC)"

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@make -s -C $(LIBFT_DIR) clean --no-print-directory > /dev/null
	@make -s -C $(MLX_DIR) clean --no-print-directory > /dev/null

# Clean everything
fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(NC)"
	@rm -f $(NAME)
	@make -s -C $(LIBFT_DIR) fclean --no-print-directory > /dev/null

# Rebuild everything
re: fclean all

# Bonus (not implemented yet)
bonus: all

.PHONY: all clean fclean re bonus
