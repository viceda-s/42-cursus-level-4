# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/13 12:34:14 by viceda-s          #+#    #+#              #
#    Updated: 2025/10/28 15:59:54 by viceda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

# Directories
MANDATORY_DIR = mandatory
BONUS_DIR = bonus
LIB_DIR = lib

# Libraries
LIBFT_DIR = $(LIB_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = $(LIB_DIR)/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

# Rules
all:
	@$(MAKE) -s -C $(MANDATORY_DIR)

bonus:
	@$(MAKE) -s -C $(BONUS_DIR)

# Clean object files
clean:
	@$(MAKE) -s -C $(MANDATORY_DIR) clean
	@$(MAKE) -s -C $(BONUS_DIR) clean

# Clean everything
fclean: clean
	@$(MAKE) -s -C $(MANDATORY_DIR) fclean
	@$(MAKE) -s -C $(BONUS_DIR) fclean
	@echo "All binaries cleaned."

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re bonus
