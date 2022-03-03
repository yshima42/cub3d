/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:08:54 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/03 22:31:01 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/cub3d.h"

void	render(t_conf *conf)
{
	conf->screen.img = mlx_new_image(conf->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	conf->screen.addr = mlx_get_data_addr(conf->screen.img, &conf->screen.bits_per_pixel,
			&conf->screen.line_length, &conf->screen.endian);
	render_3d_walls(conf);
	render_map(&conf->screen, conf->map.map);
	render_rays(&conf->screen, conf->player, conf->rays);
	render_player(&conf->screen, conf->player);
	mlx_put_image_to_window(conf->mlx_ptr, conf->win_ptr, conf->screen.img, 0, 0);
}

int	deal_key(int key, t_conf *conf)
{
	if (key == A_KEY)
		move_player(conf->map, &conf->player, conf->player.pos.x + PLAYER_SIZE * cos(normalize_angle(conf->player.angle - M_PI / 2)), conf->player.pos.y + PLAYER_SIZE * sin(normalize_angle(conf->player.angle - M_PI / 2)));
	else if (key == D_KEY)
		move_player(conf->map, &conf->player, conf->player.pos.x + PLAYER_SIZE * cos(normalize_angle(conf->player.angle + M_PI / 2)), conf->player.pos.y + PLAYER_SIZE * sin(normalize_angle(conf->player.angle + M_PI / 2)));
	else if (key == W_KEY)
		move_player(conf->map, &conf->player, conf->player.pos.x + PLAYER_SIZE * cos(conf->player.angle), conf->player.pos.y + PLAYER_SIZE * sin(conf->player.angle));
	else if (key == S_KEY)
		move_player(conf->map, &conf->player, conf->player.pos.x - PLAYER_SIZE * cos(conf->player.angle), conf->player.pos.y - PLAYER_SIZE * sin(conf->player.angle));
	else if (key == LEFT_KEY)
	{
		conf->player.angle -= M_PI * ROTATE_SPEED;
		conf->player.angle = normalize_angle(conf->player.angle);
		conf->player.pdx = cos(conf->player.angle);
		conf->player.pdy = sin(conf->player.angle);
	}
	else if (key == RIGHT_KEY)
	{
		conf->player.angle += M_PI * ROTATE_SPEED;
		conf->player.angle = normalize_angle(conf->player.angle);
		conf->player.pdx = cos(conf->player.angle);
		conf->player.pdy = sin(conf->player.angle);
	}
	set_rays(conf);
	render(conf);
	return (0);
}

void	init_conf(t_conf *conf)
{
	*conf = (t_conf){};
	conf->player.pos.x = 80;
	conf->player.pos.y = 80;
	conf->color_buffer = (size_t *)malloc(sizeof(size_t) * WINDOW_WIDTH * WINDOW_HEIGHT);
}

void	map_check(char **map, t_conf *conf)
{
	rectangular_check(map, conf);
	wall_check(map, conf);
	array_loop(map, conf, invalid_char_check);
	array_loop(map, conf, inmap_char_count);
	//n_char_check(map, conf);
}

char	**map_set(char *mapfile, t_conf *conf)
{
	int		fd;
	t_list	*buf;

	buf = NULL;
	fd = ft_open_readfile(mapfile);
	conf->map.height = fd_to_lst(fd, &buf);
	size_check(conf);
	return (lst_to_array(buf, conf->map.height));
}

void	exit_tmp(t_conf *conf)
{
	(void)conf;
	free(conf->color_buffer);
	exit(0);
}

int	main(int ac, char *av[])
{
	t_conf	conf;

	args_check(ac, av);
	init_conf(&conf);
	conf.mlx_ptr = mlx_init();
	conf.win_ptr = mlx_new_window(conf.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	conf.map.map = map_set(av[1], &conf);
	map_check(conf.map.map, &conf);	
	set_rays(&conf);
	render(&conf);
	mlx_hook(conf.win_ptr, 2, 1L << 0, deal_key, &conf);
	mlx_loop(conf.mlx_ptr);
}
