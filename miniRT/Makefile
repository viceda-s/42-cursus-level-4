NAME = miniRT

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./inc -I./lib/minilibx-linux -I./lib/libft/include

MLX_PATH	= lib/minilibx-linux/
MLX_LIB		= $(MLX_PATH)libmlx.a
MLX_FLAGS 	= -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

LIBFT_PATH	= lib/libft/
LIBFT_LIB	= $(LIBFT_PATH)libft.a

SRCS = main.c src/event.c
OBJS = $(SRCS:.c=.o)

all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)

$(MLX_LIB):
	@make -C $(MLX_PATH)

$(LIBFT_LIB):
	@make -C $(LIBFT_PATH)

$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT_LIB)
	$(CC) $(OBJS) $(MLX_LIB) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	@make -C $(MLX_PATH) clean
	@make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(MLX_PATH) clean
	@make -C $(LIBFT_PATH) fclean

re: fclean all

test: $(NAME)
	./$(NAME)

.PHONY: all clean fclean re test
