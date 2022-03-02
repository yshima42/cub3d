/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 21:56:57 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/02 14:53:58 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdint.h>
# include <math.h>
# include <stdbool.h>
# include <limits.h>

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"


# define VALID_CHAR 		"01CEP"

# define IMG_EMPTY 			"images/empty.xpm"
# define IMG_WALL 			"images/wall.xpm"
# define IMG_COLLECTIBLE	"images/coin_colored.xpm"
# define IMG_EXIT 			"images/exit.xpm"
# define IMG_PLAYER 		"images/player1.xpm"
# define IMG_PLAYER_2		"images/player2.xpm"

# define MINIMAP_SCALE 1
# define TILE_SIZE 			32 * MINIMAP_SCALE
# define SCREEN_SIZE 		20
# define PLAYER_SIZE 		8 * MINIMAP_SCALE

#define FOV_ANGLE (60 * (M_PI / 180))
#define TWO_PI M_PI * 2

#define WALL_STRIP_WIDTH 1

# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define LEFT_KEY 65361
# define RIGHT_KEY 65363

# define ROTATE_SPEED 1/60

# define WINDOW_WIDTH 1500
# define WINDOW_HEIGHT 1000

# define MINIMAP_WIDTH 1500
# define MINIMAP_HEIGHT 1000

# define DIST_TO_PROJECTION (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2)

# define RIGHT 1 << 0
# define LEFT 1 << 1
# define UP 1 << 2
# define DOWN 1 << 3


#define NUM_RAYS WINDOW_WIDTH / WALL_STRIP_WIDTH

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

typedef struct s_xy {
	double x;
	double y;
}				t_xy;

typedef struct s_ray {
	double	angle;
	double	distance;
	t_xy	wall_hit_pos;
	size_t	facing_to;
	size_t	found_horz_wall_hit;
	size_t	found_vert_wall_hit;
	size_t	was_hit_vertical;
	size_t	wall_hit_content;
}				t_ray;

typedef struct s_3d {
	double	wall_strip_height;
	double	wall_top;
	double	wall_bottom;
}			t_3d;

typedef struct s_player {
	t_xy pos;
	double pdx;
	double pdy;
	double angle;
}	t_player;

typedef struct s_conf {
	void		*mlx_ptr;
	void		*win_ptr;
	t_player	player;
	t_map		map;
	t_images	images;
	t_data		screen;
	t_ray		rays[NUM_RAYS];
	size_t		*color_buffer;
}				t_conf;

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

//main.c
void render(t_conf *conf);

#endif