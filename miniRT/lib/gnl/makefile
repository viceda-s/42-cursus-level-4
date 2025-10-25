# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbaldin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/15 18:00:00 by rbaldin           #+#    #+#              #
#    Updated: 2025/10/10 18:47:50 by rbaldin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

# Mandatory files
SRCS = get_next_line.c \
       get_next_line_utils.c

# Bonus files
SRCS_BONUS = get_next_line_bonus.c \
             get_next_line_utils_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

# Default target
all: $(NAME)

# Compile mandatory version
$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

# Compile bonus version
bonus: $(OBJS_BONUS)
	$(AR) $(NAME) $(OBJS_BONUS)

# Pattern rule for object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

# Clean everything
fclean: clean
	$(RM) $(NAME)

# Rebuild
re: fclean all

.PHONY: all bonus clean fclean re
