# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/13 12:34:14 by viceda-s          #+#    #+#              #
#    Updated: 2025/10/18 20:10:34 by viceda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ═══════════════════════════════════════════════════════════════════════════ #
#                              PROJECT CONFIG                                  #
# ═══════════════════════════════════════════════════════════════════════════ #

NAME = miniRT

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./inc -I./lib/minilibx-linux -I./lib/libft/include

# ═══════════════════════════════════════════════════════════════════════════ #
#                              DIRECTORIES                                     #
# ═══════════════════════════════════════════════════════════════════════════ #

SRC_DIR = src
OBJ_DIR = obj

# Library paths
MLX_PATH = lib/minilibx-linux/
LIBFT_PATH = lib/libft/

# ═══════════════════════════════════════════════════════════════════════════ #
#                              LIBRARIES                                       #
# ═══════════════════════════════════════════════════════════════════════════ #

MLX_LIB = $(MLX_PATH)libmlx.a
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

LIBFT_LIB = $(LIBFT_PATH)libft.a

# ═══════════════════════════════════════════════════════════════════════════ #
#                              SOURCE FILES (ONLY EXISTING FILES)             #
# ═══════════════════════════════════════════════════════════════════════════ #

# Main file (root directory)
MAIN_SRCS = main.c

# Existing source files in src/
SRC_SRCS = parsing/load_scene.c \
           parsing/parsing.c \
           parsing/parse_utils.c \
           utils/xyz_extraction.c \
           objects/sphere.c \
           objects/object.c \
           math/ray/ray_ops.c

# Add vector files if they exist
# math/vector/vector_ops.c \
# math/vector/vector_geo.c \

# Combine all sources
SRCS = $(MAIN_SRCS) $(addprefix $(SRC_DIR)/, $(SRC_SRCS))

# Object files
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# ═══════════════════════════════════════════════════════════════════════════ #
#                              COLORS                                          #
# ═══════════════════════════════════════════════════════════════════════════ #

GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
YELLOW = \033[0;33m
NC = \033[0m

# ═══════════════════════════════════════════════════════════════════════════ #
#                              RULES                                           #
# ═══════════════════════════════════════════════════════════════════════════ #

all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT_LIB)
	@echo "$(BLUE)Linking $(NAME)...$(NC)"
	@$(CC) $(OBJS) $(MLX_LIB) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(NC)"

# Compile object files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Library rules
$(MLX_LIB):
	@echo "$(BLUE)Building MiniLibX...$(NC)"
	@make -C $(MLX_PATH) 2>/dev/null || (echo "$(RED)Error building MiniLibX$(NC)" && exit 1)

$(LIBFT_LIB):
	@echo "$(BLUE)Building libft...$(NC)"
	@make -C $(LIBFT_PATH) 2>/dev/null || (echo "$(RED)Error building libft$(NC)" && exit 1)

# ═══════════════════════════════════════════════════════════════════════════ #
#                              CLEANING                                        #
# ═══════════════════════════════════════════════════════════════════════════ #

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@make -C $(MLX_PATH) clean 2>/dev/null || true
	@make -C $(LIBFT_PATH) clean 2>/dev/null || true

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(NC)"
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean 2>/dev/null || true

re: fclean all

# ═══════════════════════════════════════════════════════════════════════════ #
#                              DEBUG & UTILITIES                               #
# ═══════════════════════════════════════════════════════════════════════════ #

debug: CFLAGS += -fsanitize=address -fsanitize=undefined
debug: $(NAME)

show-files:
	@echo "$(BLUE)Source files:$(NC)"
	@echo $(SRCS) | tr ' ' '\n'

check-files:
	@echo "$(BLUE)Checking if source files exist:$(NC)"
	@for file in $(SRCS); do \
		if [ -f $$file ]; then \
			echo "$(GREEN)✓ $$file$(NC)"; \
		else \
			echo "$(RED)✗ $$file$(NC)"; \
		fi; \
	done

.PHONY: all clean fclean re debug check-files show-files
