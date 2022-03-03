/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 21:56:57 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/02 17:26:57 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <stdint.h>

# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"

typedef struct s_uni
{
	int		pos_y;
	int		pos_x;
}	t_uni;

typedef struct s_enemy
{
	int		pos_y;
	int		pos_x;
}	t_enemy;

typedef struct s_player
{
	int		pos_y;
	int		pos_x;
	size_t	n_steps;
	size_t	n_clicks;
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
	size_t	n_enemies;
	size_t	n_unis;
}	t_map;

typedef struct s_images
{
	void	*empty;
	void	*wall;
	void	*collectible;
	void	*exit;
	void	*player;
	void	*player2;
	void	*player3;
	void	*player4;
	void	*player5;
	void	*enemy;
	void	*enemy2;
	void	*uni;
	int		size;
}	t_images;

typedef struct s_conf
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_images	images;
	t_player	player;
	t_enemy		enemy;
	t_enemy		uni;
}	t_conf;

# define VALID_CHAR 		"01CEPTU"

# define IMG_EMPTY 			"images/empty.xpm"
# define IMG_WALL 			"images/wall.xpm"
# define IMG_COLLECTIBLE	"images/coin_colored.xpm"
# define IMG_EXIT 			"images/exit.xpm"
# define IMG_PLAYER 		"images/player1.xpm"
# define IMG_PLAYER_2		"images/player2.xpm"
# define IMG_PLAYER_3		"images/player3.xpm"
# define IMG_PLAYER_4		"images/player4.xpm"
# define IMG_PLAYER_5		"images/player5.xpm"
# define IMG_ENEMY_1		"images/ripple1.xpm"
# define IMG_ENEMY_2		"images/ripple2.xpm"
# define IMG_UNICORN_1		"images/uni1.xpm"
# define IMG_UNICORN_2		"images/uni2.xpm"

# define CHIP_SIZE 			32
# define SCREAN_SIZE 		20

# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100

//main_bonus.c
void	pos_check(char **map, t_conf *conf);

//animation_bonus.c
void	chip_ani(int pos_y, int pos_x, void *img_ptr, t_conf *conf);
int		animation(t_conf *conf);
int		expose(t_conf *conf);

//enemy_bonus.c
void	uni_move(int u_y, int u_x, t_conf *conf);
void	enemy_move(int e_y, int e_x, t_conf *conf);

//error_output_bonus.c
void	map_error_output(char **map, char *output);
void	perror_exit(char *error_message);
void	error_mlx(t_conf *conf);
void	args_check(int ac, char **av);

//free_bonus.c
char	**ft_arrayfree(char **tab);
void	free_mlx_win(t_conf *conf);
int		free_all_exit(t_conf *conf);

//initialize_bonus.c
void	initialize_conf(t_conf *conf);
void	initialize_conf2(t_conf *conf);

//map_check_bonus.c
void	rectangular_check(char **map, t_conf *conf);
void	wall_check(char **map, t_conf *conf);
char	*invalid_char_check(char c, t_conf *conf);
char	*inmap_char_count(char c, t_conf *conf);
void	n_char_check(char **map, t_conf *conf);

//mlx_bonus.c
void	array_to_screan(char **map, t_conf *conf);
void	display_mlx(t_conf *conf);
void	hook_loop_mlx(t_conf *conf);

//player_action_bonus.c
int		next_pos_check(char next_pos_c, char check_c);
void	collect_item(char *a, char *b, t_conf *conf);
void	game_finish_animation(void *img1, void *img2, t_conf *conf);

//player_move_bonus.c
void	player_move(int keycode, t_conf *conf);
void	step_to_next(char *current_pos, char *next_pos, t_conf *conf);
void	game_complete(char *a, char *b, t_conf *conf);

//sl_utils_bonus.c
void	*chr_to_imgptr(char c, t_conf *conf);
void	chip_set(t_conf *conf);
void	chip_set2(t_conf *conf);
void	step_counter(t_conf *conf);
void	size_check(t_conf *conf);

//utils_bonus.c
void	array_loop(char **map, t_conf *conf, char *f(char c, t_conf *conf));
int		ft_open_readfile(char *readfile);
char	**lst_to_array(t_list *buf, size_t height);
size_t	fd_to_lst(int fd, t_list **buf);
void	ft_swap(char *a, char *b);

#endif