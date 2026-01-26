# **************************************************************************** #
#                           cub3D by avigna and viceda-s                       #
# **************************************************************************** #

# =========================
#        CONFIGURATION
# =========================

NAME		= cub3D
BONUS		= cub3D_bonus
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
RM			= rm -f

INCLUDES	= -Iinc -Ilib/libft/include -Ilib/minilibx-linux

LIBFT_DIR	= lib/libft
LIBFT		= $(LIBFT_DIR)/libft.a
MLX_DIR		= lib/minilibx-linux
MLX			= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm

OBJS_DIR	= obj
SRC_DIR		= src

# =========================
#       SOURCE FILES
# =========================

SRCS		= \
$(SRC_DIR)/main.c \
$(SRC_DIR)/core/cleanup.c \
$(SRC_DIR)/core/error.c \
$(SRC_DIR)/core/events.c \
$(SRC_DIR)/core/init.c \
$(SRC_DIR)/core/init_player.c \
$(SRC_DIR)/core/keys.c \
$(SRC_DIR)/core/load_textures.c \
$(SRC_DIR)/parsing/parse_colors.c \
$(SRC_DIR)/parsing/parse_file.c \
$(SRC_DIR)/parsing/parse_map.c \
$(SRC_DIR)/parsing/parse_rgb.c \
$(SRC_DIR)/parsing/parse_texture.c \
$(SRC_DIR)/parsing/parse_utils.c \
$(SRC_DIR)/parsing/validate.c \
$(SRC_DIR)/player/movement.c \
$(SRC_DIR)/player/rotation.c \
$(SRC_DIR)/raycasting/dda.c \
$(SRC_DIR)/raycasting/raycast.c \
$(SRC_DIR)/raycasting/textures.c \
$(SRC_DIR)/raycasting/walls.c \
$(SRC_DIR)/render/draw.c \
$(SRC_DIR)/render/render.c

# =========================
#      BONUS FILES
# =========================

BONUS_SRC_DIR = bonus/src_bonus

BONUS_SRCS	= \
$(BONUS_SRC_DIR)/main_bonus.c \
$(BONUS_SRC_DIR)/core/cleanup_bonus.c \
$(BONUS_SRC_DIR)/core/cleanup_utils_bonus.c \
$(BONUS_SRC_DIR)/core/error_bonus.c \
$(BONUS_SRC_DIR)/core/events_bonus.c \
$(BONUS_SRC_DIR)/core/init_bonus.c \
$(BONUS_SRC_DIR)/core/init_player_bonus.c \
$(BONUS_SRC_DIR)/core/input_bonus.c \
$(BONUS_SRC_DIR)/core/keys_bonus.c \
$(BONUS_SRC_DIR)/core/load_textures_bonus.c \
$(BONUS_SRC_DIR)/parsing/parse_colors_bonus.c \
$(BONUS_SRC_DIR)/parsing/parse_file_bonus.c \
$(BONUS_SRC_DIR)/parsing/parse_map_bonus.c \
$(BONUS_SRC_DIR)/parsing/parse_rgb_bonus.c \
$(BONUS_SRC_DIR)/parsing/parse_texture_bonus.c \
$(BONUS_SRC_DIR)/parsing/parse_utils_bonus.c \
$(BONUS_SRC_DIR)/parsing/validate_bonus.c \
$(BONUS_SRC_DIR)/parsing/validate_utils_bonus.c \
$(BONUS_SRC_DIR)/player/collision_bonus.c \
$(BONUS_SRC_DIR)/player/mouse_bonus.c \
$(BONUS_SRC_DIR)/player/movement_bonus.c \
$(BONUS_SRC_DIR)/player/rotation_bonus.c \
$(BONUS_SRC_DIR)/raycasting/dda_bonus.c \
$(BONUS_SRC_DIR)/raycasting/dda_utils_bonus.c \
$(BONUS_SRC_DIR)/raycasting/raycast_bonus.c \
$(BONUS_SRC_DIR)/raycasting/textures_bonus.c \
$(BONUS_SRC_DIR)/raycasting/textures_utils_bonus.c \
$(BONUS_SRC_DIR)/raycasting/walls_bonus.c \
$(BONUS_SRC_DIR)/render/crosshair_bonus.c \
$(BONUS_SRC_DIR)/render/draw_bonus.c \
$(BONUS_SRC_DIR)/render/draw_utils_bonus.c \
$(BONUS_SRC_DIR)/render/minimap_bonus.c \
$(BONUS_SRC_DIR)/render/minimap_draw_bonus.c \
$(BONUS_SRC_DIR)/render/minimap_targets_bonus.c \
$(BONUS_SRC_DIR)/render/render_bonus.c \
$(BONUS_SRC_DIR)/doors/doors_bonus.c \
$(BONUS_SRC_DIR)/doors/doors_utils_bonus.c \
$(BONUS_SRC_DIR)/sprites/sprite_render_bonus.c \
$(BONUS_SRC_DIR)/sprites/sprite_utils_bonus.c \
$(BONUS_SRC_DIR)/sprites/target_bonus.c \
$(BONUS_SRC_DIR)/sprites/target_cleared_bonus.c \
$(BONUS_SRC_DIR)/sprites/target_hit_bonus.c \
$(BONUS_SRC_DIR)/sprites/target_mission_bonus.c \
$(BONUS_SRC_DIR)/sprites/target_score_bonus.c \
$(BONUS_SRC_DIR)/sprites/target_textures_bonus.c \
$(BONUS_SRC_DIR)/weapon/weapon_bonus.c \
$(BONUS_SRC_DIR)/weapon/weapon_draw_bonus.c \
$(BONUS_SRC_DIR)/weapon/weapon_anim_bonus.c

# =========================
#     OBJECT FILES
# =========================

OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:$(SRC_DIR)/%.c=%.o))
BONUS_OBJS	= $(addprefix $(OBJS_DIR)/bonus/, $(BONUS_SRCS:$(BONUS_SRC_DIR)/%.c=%.o))

# Progress tracking
TOTAL_SRCS	= $(words $(SRCS))
BONUS_TOTAL	= $(words $(BONUS_SRCS))
CURRENT		= 0

# =========================
#         COLORS
# =========================

ORANGE		= \033[38;5;208m
AMBER		= \033[38;5;214m
GREEN		= \033[0;32m
YELLOW		= \033[1;33m
RED			= \033[0;31m
BLUE		= \033[0;34m
BOLD		= \033[1m
RESET		= \033[0m

# =========================
#          RULES
# =========================

all: print_header $(NAME)

print_header:
	@echo "$(AMBER)                     █████      $(ORANGE)████████  ██████████  $(RESET)"
	@echo "$(AMBER)                    ░░███      $(ORANGE)███░░░░███░░███░░░░███ $(RESET)"
	@echo "$(AMBER)  ██████  █████ ████ ░███████ $(ORANGE)░░░    ░███ ░███   ░░███$(RESET)"
	@echo "$(AMBER) ███░░███░░███ ░███  ░███░░███   $(ORANGE)██████░  ░███    ░███$(RESET)"
	@echo "$(AMBER)░███ ░░░  ░███ ░███  ░███ ░███  $(ORANGE)░░░░░░███ ░███    ░███$(RESET)"
	@echo "$(AMBER)░███  ███ ░███ ░███  ░███ ░███ $(ORANGE)███   ░███ ░███    ███ $(RESET)"
	@echo "$(AMBER)░░██████  ░░████████ ████████ $(ORANGE)░░████████  ██████████  $(RESET)"
	@echo "$(AMBER) ░░░░░░    ░░░░░░░░ ░░░░░░░░   $(ORANGE)░░░░░░░░  ░░░░░░░░░░   $(RESET)"
	@echo "\033[38;5;166m                               𝙗𝙮 𝙖𝙫𝙞𝙜𝙣𝙖 𝙖𝙣𝙙 𝙫𝙞𝙘𝙚𝙙𝙖-𝙨 "
	@echo "$(RESET)"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/core
	@mkdir -p $(OBJS_DIR)/parsing
	@mkdir -p $(OBJS_DIR)/player
	@mkdir -p $(OBJS_DIR)/raycasting
	@mkdir -p $(OBJS_DIR)/render
	@mkdir -p $(OBJS_DIR)/bonus/core
	@mkdir -p $(OBJS_DIR)/bonus/parsing
	@mkdir -p $(OBJS_DIR)/bonus/player
	@mkdir -p $(OBJS_DIR)/bonus/raycasting
	@mkdir -p $(OBJS_DIR)/bonus/render

$(NAME): $(OBJS_DIR) print_lib_header $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(BOLD)$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

print_lib_header:
	@echo ""
	@echo "$(BOLD)$(AMBER)Compiling libraries...$(RESET)"

$(LIBFT):
	@printf "$(AMBER)[1/2]$(RESET) Compiling libft... "
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory > /dev/null 2>&1
	@echo "$(GREEN)✓$(RESET)"

$(MLX):
	@printf "$(AMBER)[2/2]$(RESET) Compiling minilibx... "
	@$(MAKE) -C $(MLX_DIR) --no-print-directory > /dev/null 2>&1
	@echo "$(GREEN)✓$(RESET)"
	@echo ""
	@echo "$(BOLD)$(GREEN)✓ All libraries compiled successfully!$(RESET)"
	@echo ""

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(eval IS_BONUS=$(filter bonus,$(MAKECMDGOALS)))
	@$(eval TARGET=$(if $(IS_BONUS),cub3D_bonus,cub3D))
	@$(eval TOTAL=$(if $(IS_BONUS),$(BONUS_TOTAL),$(TOTAL_SRCS)))
	@$(eval CURRENT=$(shell find $(OBJS_DIR) -name '*.o' 2>/dev/null | wc -l))
	@$(eval PERCENT=$(shell echo $$(($(CURRENT) * 100 / $(TOTAL)))))
	@$(eval FILLED=$(shell echo $$(($(PERCENT) / 2))))
	@$(eval EMPTY=$(shell echo $$((50 - $(FILLED)))))
	@if [ $(CURRENT) -eq 0 ]; then printf "\n$(BOLD)$(BLUE)Compiling $(TARGET):$(RESET)\n"; fi
	@printf "[$(GREEN)"
	@for i in $$(seq 1 $(FILLED)); do printf "█"; done
	@printf "$(RESET)"
	@for i in $$(seq 1 $(EMPTY)); do printf "░"; done
	@printf "$(RESET)] $(YELLOW)%3d%%$(RESET) %-25s\r" $(PERCENT) "$(notdir $<)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@if [ $(CURRENT) -eq $$(($(TOTAL) - 1)) ]; then \
		printf "[$(GREEN)"; \
		for i in $$(seq 1 50); do printf "█"; done; \
		printf "$(RESET)] $(GREEN)100%%$(RESET)                          \n"; \
	fi

bonus: clean_bonus_objs print_header $(BONUS)

clean_bonus_objs:
	@$(RM) -r $(OBJS_DIR)

$(BONUS): $(OBJS_DIR) print_lib_header $(LIBFT) $(MLX) $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(BONUS_OBJS) $(LIBFT) $(MLX_FLAGS) -o $(BONUS)
	@echo "$(BOLD)$(GREEN)✓ $(BONUS) compiled successfully!$(RESET)"

$(OBJS_DIR)/bonus/%.o: $(BONUS_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(eval CURRENT=$(shell find $(OBJS_DIR)/bonus -name '*.o' 2>/dev/null | wc -l))
	@$(eval PERCENT=$(shell echo $$(($(CURRENT) * 100 / $(BONUS_TOTAL)))))
	@$(eval FILLED=$(shell echo $$(($(PERCENT) / 2))))
	@$(eval EMPTY=$(shell echo $$((50 - $(FILLED)))))
	@if [ $(CURRENT) -eq 0 ]; then printf "\n$(BOLD)$(BLUE)Compiling cub3D_bonus:$(RESET)\n"; fi
	@printf "[$(GREEN)"
	@for i in $$(seq 1 $(FILLED)); do printf "█"; done
	@printf "$(RESET)"
	@for i in $$(seq 1 $(EMPTY)); do printf "░"; done
	@printf "$(RESET)] $(YELLOW)%3d%%$(RESET) %-25s\r" $(PERCENT) "$(notdir $<)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@if [ $(CURRENT) -eq $$(($(BONUS_TOTAL) - 1)) ]; then \
		printf "[$(GREEN)"; \
		for i in $$(seq 1 50); do printf "█"; done; \
		printf "$(RESET)] $(GREEN)100%%$(RESET)                          \n"; \
	fi

clean:
	@printf "\n$(BOLD)$(RED)Cleaning:$(RESET)\n"
	@printf "[$(RED)██████████████████████████████████████████████████$(RESET)] $(YELLOW)Removing objects...$(RESET)\r"
	@$(RM) -r $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory > /dev/null 2>&1
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory > /dev/null 2>&1
	@printf "[$(GREEN)██████████████████████████████████████████████████$(RESET)] $(GREEN)100%%$(RESET)                         \n"
	@echo "$(BOLD)$(GREEN)✓ Clean completed!$(RESET)"
	@echo ""

fclean: 
	@printf "\n$(BOLD)$(RED)Full cleaning:$(RESET)\n"
	@printf "[$(RED)████████████$(RESET)░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░] $(YELLOW) 25%%$(RESET) Removing objects...\r"
	@$(RM) -r $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory > /dev/null 2>&1
	@printf "[$(RED)█████████████████████████$(RESET)░░░░░░░░░░░░░░░░░░░░░░░░░] $(YELLOW) 50%%$(RESET) Removing executables...\r"
	@$(RM) $(NAME) $(BONUS)
	@printf "[$(RED)█████████████████████████████████████$(RESET)░░░░░░░░░░░░░] $(YELLOW) 75%%$(RESET) Cleaning libraries...\r"
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory > /dev/null 2>&1
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory > /dev/null 2>&1
	@printf "[$(GREEN)██████████████████████████████████████████████████$(RESET)] $(GREEN)100%%$(RESET)                             \n"
	@echo "$(BOLD)$(GREEN)✓ Full clean completed!$(RESET)"
	@echo ""

re: fclean all

.PHONY: all clean fclean re bonus print_header clean_bonus_objs print_lib_header
