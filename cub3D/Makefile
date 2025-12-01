# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/01 15:53:19 by viceda-s          #+#    #+#              #
#    Updated: 2025/12/01 15:54:02 by viceda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

# Directories
SRC_DIR = src
BONUS_DIR = bonus
LIB_DIR = lib

# Libraries
LIBFT_DIR = $(LIB_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = $(LIB_DIR)/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

# Rules
all:
	@$(MAKE) -s -C $(SRC_DIR)

bonus:
	@$(MAKE) -s -C $(BONUS_DIR)

# Clean object files
clean:
	@$(MAKE) -s -C $(SRC_DIR) clean
	@$(MAKE) -s -C $(BONUS_DIR) clean

# Clean everything
fclean: clean
	@$(MAKE) -s -C $(SRC_DIR) fclean
	@$(MAKE) -s -C $(BONUS_DIR) fclean
	@echo "All binaries cleaned."

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re bonus
