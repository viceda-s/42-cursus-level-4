# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 14:02:31 by viceda-s          #+#    #+#              #
#    Updated: 2026/01/06 15:14:16 by viceda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# =========================
#        CONFIGURATION
# =========================

NAME		= libft.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs
RM			= rm -f

INCLUDES	= -Iinclude

OBJS_DIR	= obj
SRCS_DIR	= src
CHAR_DIR	= $(SRCS_DIR)/char
STRING_DIR	= $(SRCS_DIR)/string
MEMORY_DIR	= $(SRCS_DIR)/memory
CONVER_DIR	= $(SRCS_DIR)/conversion
FD_DIR		= $(SRCS_DIR)/fd
LIST_DIR	= $(SRCS_DIR)/list
PRINTF_DIR	= $(SRCS_DIR)/ft_printf
GNL_DIR		= $(SRCS_DIR)/gnl

# =========================
#       SOURCE FILES
# =========================

SRCS		= \
$(CHAR_DIR)/ft_isalpha.c \
$(CHAR_DIR)/ft_isdigit.c \
$(CHAR_DIR)/ft_isalnum.c \
$(CHAR_DIR)/ft_isascii.c \
$(CHAR_DIR)/ft_isprint.c \
$(CHAR_DIR)/ft_toupper.c \
$(CHAR_DIR)/ft_tolower.c \
\
$(STRING_DIR)/ft_strlen.c \
$(STRING_DIR)/ft_strlcpy.c \
$(STRING_DIR)/ft_strlcat.c \
$(STRING_DIR)/ft_strchr.c \
$(STRING_DIR)/ft_strrchr.c \
$(STRING_DIR)/ft_strncmp.c \
$(STRING_DIR)/ft_strnstr.c \
$(STRING_DIR)/ft_strdup.c \
$(STRING_DIR)/ft_substr.c \
$(STRING_DIR)/ft_strjoin.c \
$(STRING_DIR)/ft_strtrim.c \
$(STRING_DIR)/ft_split.c \
$(STRING_DIR)/ft_strmapi.c \
$(STRING_DIR)/ft_striteri.c \
\
$(MEMORY_DIR)/ft_memset.c \
$(MEMORY_DIR)/ft_bzero.c \
$(MEMORY_DIR)/ft_memcpy.c \
$(MEMORY_DIR)/ft_memmove.c \
$(MEMORY_DIR)/ft_memchr.c \
$(MEMORY_DIR)/ft_memcmp.c \
$(MEMORY_DIR)/ft_calloc.c \
\
$(FD_DIR)/ft_putchar_fd.c \
$(FD_DIR)/ft_putstr_fd.c \
$(FD_DIR)/ft_putendl_fd.c \
$(FD_DIR)/ft_putnbr_fd.c \
\
$(CONVER_DIR)/ft_atoi.c \
$(CONVER_DIR)/ft_itoa.c \
\
$(LIST_DIR)/ft_lstnew.c \
$(LIST_DIR)/ft_lstadd_front.c \
$(LIST_DIR)/ft_lstsize.c \
$(LIST_DIR)/ft_lstlast.c \
$(LIST_DIR)/ft_lstadd_back.c \
$(LIST_DIR)/ft_lstdelone.c \
$(LIST_DIR)/ft_lstclear.c \
$(LIST_DIR)/ft_lstiter.c \
$(LIST_DIR)/ft_lstmap.c \
\
$(PRINTF_DIR)/ft_printf.c \
$(PRINTF_DIR)/ft_printf_numbers.c \
$(PRINTF_DIR)/ft_printf_utils.c \
\
$(GNL_DIR)/get_next_line_bonus.c

# =========================
#      BONUS FILES
# =========================

BONUS_SRCS	= \
$(GNL_DIR)/get_next_line_bonus.c \
\
$(LIST_DIR)/ft_lstnew.c \
$(LIST_DIR)/ft_lstadd_front.c \
$(LIST_DIR)/ft_lstsize.c \
$(LIST_DIR)/ft_lstlast.c \
$(LIST_DIR)/ft_lstadd_back.c \
$(LIST_DIR)/ft_lstdelone.c \
$(LIST_DIR)/ft_lstclear.c \
$(LIST_DIR)/ft_lstiter.c \
$(LIST_DIR)/ft_lstmap.c

# =========================
#     OBJECT FILES
# =========================

OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
BONUS_OBJS	= $(addprefix $(OBJS_DIR)/, $(BONUS_SRCS:.c=.o))

# Progress tracking
TOTAL_FILES = $(words $(SRCS))

# =========================
#         COLORS
# =========================

GREEN		= \033[0;32m
YELLOW		= \033[1;33m
RED			= \033[0;31m
BLUE		= \033[0;34m
BOLD		= \033[1m
RESET		= \033[0m

# =========================
#          RULES
# =========================

all: $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/$(CHAR_DIR)
	@mkdir -p $(OBJS_DIR)/$(STRING_DIR)
	@mkdir -p $(OBJS_DIR)/$(MEMORY_DIR)
	@mkdir -p $(OBJS_DIR)/$(CONVER_DIR)
	@mkdir -p $(OBJS_DIR)/$(FD_DIR)
	@mkdir -p $(OBJS_DIR)/$(LIST_DIR)
	@mkdir -p $(OBJS_DIR)/$(PRINTF_DIR)
	@mkdir -p $(OBJS_DIR)/$(GNL_DIR)

$(NAME): $(OBJS_DIR) $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "$(BOLD)$(GREEN)✓ libft compiled successfully!$(RESET)"

bonus: $(OBJS_DIR) $(OBJS) $(BONUS_OBJS)
	@$(AR) $(NAME) $(OBJS) $(BONUS_OBJS)
	@echo "$(BOLD)$(GREEN)✓ libft with bonus compiled successfully!$(RESET)"

$(OBJS_DIR)/%.o: %.c
	@current=$$(find $(OBJS_DIR) -name "*.o" 2>/dev/null | wc -l | tr -d ' '); \
	current=$$((current + 1)); \
	percentage=$$((current * 100 / $(TOTAL_FILES))); \
	filled=$$((percentage / 2)); \
	empty=$$((50 - filled)); \
	if [ $$current -eq 1 ]; then printf "\n$(BOLD)$(BLUE)Compiling libft:$(RESET)\n"; fi; \
	printf "[$(GREEN)"; \
	for i in $$(seq 1 $$filled); do printf "█"; done; \
	printf "$(RESET)"; \
	for i in $$(seq 1 $$empty); do printf "░"; done; \
	printf "$(RESET)] $(YELLOW)%3d%%$(RESET) %-25s\r" "$$percentage" "$(notdir $<)"; \
	if [ $$current -eq $(TOTAL_FILES) ]; then \
		printf "[$(GREEN)"; \
		for i in $$(seq 1 50); do printf "█"; done; \
		printf "$(RESET)] $(GREEN)100%%$(RESET)                           \n"; \
	fi
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@printf "[$(RED)██████████████████████████████████████████████████$(RESET)] $(YELLOW)Removing objects...$(RESET)\r"
	@$(RM) -r $(OBJS_DIR)
	@printf "[$(GREEN)██████████████████████████████████████████████████$(RESET)] $(GREEN)100%%$(RESET)                \n"

fclean:
	@printf "[$(RED)█████████████████████████$(RESET)░░░░░░░░░░░░░░░░░░░░░░░░░] $(YELLOW) 50%%$(RESET) Removing objects...\r"
	@$(RM) -r $(OBJS_DIR)
	@printf "[$(RED)██████████████████████████████████████████████████$(RESET)] $(YELLOW)100%%$(RESET) Removing library...\r"
	@$(RM) $(NAME)
	@printf "[$(GREEN)██████████████████████████████████████████████████$(RESET)] $(GREEN)100%%$(RESET)                    \n"

re: fclean all

.PHONY: all bonus clean fclean re
