CC				= 	gcc
CFLAGS			= 	-Wall -Wextra -Werror
NAME			= 	cub3d
INCLUDES		= 	includes
SRCS_PATH		= 	./srcs/
BONUS_PATH		= 	./srcs_bonus/
LIBFT_PATH		= 	./libft/
MLX_PATH		= 	./mlx_linux/
SRCS_FILES    	= 	$(SRCS_PATH)main.c $(SRCS_PATH)utils.c $(SRCS_PATH)map_check.c \
					$(SRCS_PATH)free.c $(SRCS_PATH)sl_utils.c $(SRCS_PATH)player_move.c \
					$(SRCS_PATH)error.c $(SRCS_PATH)mlx.c
BONUS_FILES    	= 	$(BONUS_PATH)main_bonus.c $(BONUS_PATH)utils_bonus.c $(BONUS_PATH)map_check_bonus.c \
					$(BONUS_PATH)free_bonus.c $(BONUS_PATH)sl_utils_bonus.c $(BONUS_PATH)player_move_bonus.c \
					$(BONUS_PATH)error_bonus.c $(BONUS_PATH)mlx_bonus.c $(BONUS_PATH)animation_bonus.c \
					$(BONUS_PATH)initialize_bonus.c $(BONUS_PATH)enemy_bonus.c $(BONUS_PATH)player_action_bonus.c
SRCS_OBJS		= 	$(SRCS_FILES:.c=.o)
BONUS_OBJS		= 	$(BONUS_FILES:.c=.o)

ifdef BONUS
SRCS_OBJS       = 	$(BONUS_OBJS)
endif

LIBFTMAKE		= 	$(MAKE) -C $(LIBFT_PATH)
LIBFTFLAG		= 	-L$(LIBFT_PATH) -lft
MLXMAKE			= 	$(MAKE) -C $(MLX_PATH)
MLXFLAG			= 	-Lmlx_linux -lmlx -Imlx_linux -lXext -lX11 -lm
GITMLX			= 	git clone https://github.com/42Paris/minilibx-linux.git mlx_linux

all:			$(NAME)

$(MLX_PATH):
				$(GITMLX)

$(NAME):		$(MLX_PATH) $(SRCS_OBJS)
				$(LIBFTMAKE)
				$(MLXMAKE)
				$(CC) $(CFLAGS) $(SRCS_OBJS) $(LIBFTFLAG) $(MLXFLAG) -o $(NAME)

lib:
				$(LIBFTMAKE)

mlx:
				$(MLXMAKE)

.c.o:
				$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

clean:
				$(LIBFTMAKE) clean
				$(MLXMAKE) clean
				$(RM) $(SRCS_OBJS) $(BONUS_OBJS)

fclean:			clean
				$(LIBFTMAKE) fclean
				$(RM) $(MLX_PATH)/libmlx.a
				$(RM) $(NAME) $(SRCS_PATH)$(SRCS_OBJS) $(BONUS_PATH)$(BONUS_OBJS)

re:				fclean all

bonus:			
				make BONUS=1

.PHONY:			all clean fclean bonus lib mlx re