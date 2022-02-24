CC				= 	gcc
CFLAGS			= 	-Wall -Wextra -Werror
NAME			= 	a.out
MLX_PATH		= 	./minilibx-linux/
SRCS_FILES    	= 	main.c
SRCS_OBJS		= 	$(SRCS_FILES:.c=.o)

LIBFTMAKE		= 	$(MAKE) -C $(LIBFT_PATH)
LIBFTFLAG		= 	-L$(LIBFT_PATH) -lft
MLXMAKE			= 	$(MAKE) -C $(MLX_PATH)

all:			$(NAME)


$(NAME):		$(SRCS_OBJS)
				$(LIBFTMAKE)
				$(CC) $(CFLAGS) $(SRCS_OBJS) $(LIBFTFLAG) -o $(NAME) -I/usr/X11/include -Lminilibx-linux -lmlx_Darwin -L/usr/X11/include/../lib -lXext -lX11

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
