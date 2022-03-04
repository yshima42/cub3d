/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 21:56:57 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/04 14:17:36 by yshimazu         ###   ########.fr       */
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
# include "./defs.h"

# define VALID_CHAR 		"01CEP"

# define IMG_EMPTY 			"images/empty.xpm"
# define IMG_WALL 			"images/wall.xpm"
# define IMG_COLLECTIBLE	"images/coin_colored.xpm"
# define IMG_EXIT 			"images/exit.xpm"
# define IMG_PLAYER 		"images/player1.xpm"
# define IMG_PLAYER_2		"images/player2.xpm"


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

typedef struct s_xy_d {
	double	x;
	double	y;
}				t_xy_d;

typedef struct s_xy_size_t {
	size_t	x;
	size_t	y;
}				t_xy_size_t;

typedef struct s_ray {
	double	angle;
	double	distance;
	t_xy_d	wall_hit_pos;
	size_t	facing_to;
	bool	found_horz_wall_hit;
	bool	found_vert_wall_hit;
	bool	was_hit_vertical;
	size_t	wall_hit_content;
}				t_ray;

typedef struct s_3d {
	double	wall_strip_height;
	double	wall_top;
	double	wall_bottom;
}			t_3d;

typedef struct s_player {
	t_xy_d pos;
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

//tmp
int	expose(t_conf *conf);

//graphics.c
void	my_mlx_pixel_put(t_data *data, size_t x, size_t y, t_color color);
void	squre_pixel_put(t_data *screen, t_xy_size_t pos, size_t size, t_color color);
void	rect_pixel_put(t_data *screen, t_xy_d start, double width, double height, t_color color);
void	circle_pixel_put(t_data *screen, t_xy_size_t pos, size_t radius, t_color color);

//graphics2.c
void	clear_color_buffer(t_conf *conf, t_color color);
void	render_color_buffer(t_conf *conf);
void	line_pixel_put(t_data *screen, t_xy_size_t pos, double angle, double len, t_color color);
void	line_pixel_put_2(t_data *screen, t_xy_d start, t_xy_d end, t_color color);
void	line_pixel_put_3(t_data *screen, t_xy_d start, t_xy_d end, t_color color);

//map.c
bool	has_wall_at(t_map map, double x, double y);
bool	is_inside_map(t_map map, double x, double y); 
void	render_map(t_data *screen, char **map);

//player.c
void	move_player(const t_map map, t_player *player, double new_x, double new_y);
void	render_player(t_data *screen, const t_player player);

//ray_render.c
void set_wall_hit(t_ray *ray, t_xy_d horz_wall_hit, t_xy_d vert_wall_hit, double horz_distance, double vert_distance);
void set_each_ray(t_conf *conf, t_ray *ray, const t_player player);
void set_rays(t_conf *conf);
void render_rays(t_data *screen, t_player player, t_ray *rays);

//ray_vert.c
t_xy_d calc_vert_intercept(t_ray *ray, const t_player player);
t_xy_d calc_vert_step(t_ray *ray);
t_xy_d calc_vert_wall_hit(const t_map map, t_ray *ray, t_xy_d step, t_xy_d intercept);
t_xy_d find_vert_wall(t_conf *conf, t_ray *ray, const t_player player);
double calc_vert_distance(t_ray *ray, const t_player player, t_xy_d vert_wall_hit);

//ray_horz.c
t_xy_d calc_horz_intercept(t_ray *ray, const t_player player);
t_xy_d calc_horz_step(t_ray *ray);
t_xy_d calc_horz_wall_hit(const t_map map, t_ray *ray, t_xy_d step, t_xy_d intercept);
t_xy_d find_horz_wall(t_conf *conf, t_ray *ray, const t_player player);
double calc_horz_distance(t_ray *ray, const t_player player, t_xy_d horz_wall_hit);

//ray_utils.c
double normalize_angle(double angle);
void set_facing_to(t_ray *ray);
double distance_between_points(t_xy_d start, t_xy_d end);

//wall.c
void set_ceiling_color(t_conf *conf, const t_3d info_3d, size_t *i);
void set_wall_color(t_conf *conf, const t_3d info_3d, size_t *i);
void set_floor_color(t_conf *conf, const t_3d info_3d, size_t *i);
void render_3d_walls(t_conf *conf);

//deal_key.c
int	deal_key(int key, t_conf *conf);

//deal_key2.c
void	a_key(t_map map, t_player *player);
void	d_key(t_map map, t_player *player);
void	w_key(t_map map, t_player *player);
void	s_key(t_map map, t_player *player);

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

//map_check2.c
void	size_check(t_conf *conf);

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



//main.c
void render(t_conf *conf);

#endif