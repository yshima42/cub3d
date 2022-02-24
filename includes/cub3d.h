/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 21:56:57 by yshimazu          #+#    #+#             */
/*   Updated: 2022/02/23 23:21:54 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdint.h>
# include <math.h>

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

typedef struct s_player
{
	int		pos_y;
	int		pos_x;
	size_t	n_steps;
	size_t	collectibles;
}	t_player;

typedef struct s_map
{
	char	**map;
	size_t	width;
	size_t	height;
	size_t	n_collectibles;
	size_t	n_players;
	size_t	n_exit;
}	t_map;

typedef struct s_images
{
	void	*empty;
	void	*wall;
	void	*collectible;
	void	*exit;
	void	*player;
	int		size;
}	t_images;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_ppos {
	double px;
	double py;
	double pdx;
	double pdy;
	double pa;
}	t_ppos;

typedef struct s_conf {
	void		*mlx_ptr;
	void		*win_ptr;
	t_ppos		ppos;
	t_map		map;
	t_images	images;
	t_data		screen;
}				t_conf;


# define VALID_CHAR 		"01CEP"

# define IMG_EMPTY 			"images/empty.xpm"
# define IMG_WALL 			"images/wall.xpm"
# define IMG_COLLECTIBLE	"images/coin_colored.xpm"
# define IMG_EXIT 			"images/exit.xpm"
# define IMG_PLAYER 		"images/player1.xpm"
# define IMG_PLAYER_2		"images/player2.xpm"

# define CHIP_SIZE 			32
# define SCREEN_SIZE 		20
# define PLAYER_SIZE 		8

# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define LEFT_KEY 65361
# define RIGHT_KEY 65363

# define WINDOW_WIDTH 1500
# define WINDOW_HEIGHT 1000

# define MINIMAP_WIDTH 750
# define MINIMAP_HEIGHT 1000

# define PI 3.1415926535

//utils.c
void	array_loop(char **map, t_conf *conf, char *f(char c, t_conf *conf));
int		ft_open_readfile(char *readfile);
char	**lst_to_array(t_list *buf, size_t height);
size_t	fd_to_lst(int fd, t_list **buf);
void	ft_swap(char *a, char *b);

//free.c
char	**ft_arrayfree(char **tab);
int		free_all_exit(t_conf *conf);

//map_check.c
void	rectangular_check(char **map, t_conf *conf);
void	wall_check(char **map, t_conf *conf);
char	*invalid_char_check(char c, t_conf *conf);
char	*inmap_char_count(char c, t_conf *conf);
void	n_char_check(char **map, t_conf *conf);

//error_output.c
void	map_error_output(char **map, char *output);
void	perror_exit(char *error_message);
void	error_mlx(t_conf *conf);
int		extension_check(char *filename);
void	args_check(int ac, char **av);

//mlx_utils.c
void	array_to_screan(char **map, t_conf *conf);
int		key_hook(int keycode, t_conf *conf);
void	hook_loop_mlx(t_conf *conf);
void	display_mlx(t_conf *conf);

//sl_utils.c
void	*chr_to_imgptr(char c, t_conf *conf);
void	chip_set(t_conf *conf);
void	step_counter(t_conf *conf);
void	size_check(t_conf *conf);

#endif