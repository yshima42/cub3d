/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:10:18 by yshimazu          #+#    #+#             */
/*   Updated: 2021/10/03 00:24:34 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static void	map_check(char **map, t_conf *conf)
{
	rectangular_check(map, conf);
	wall_check(map, conf);
	array_loop(map, conf, invalid_char_check);
	array_loop(map, conf, inmap_char_count);
	n_char_check(map, conf);
}

static char	**map_set(char *mapfile, t_conf *conf)
{
	int		fd;
	t_list	*buf;

	buf = NULL;
	fd = ft_open_readfile(mapfile);
	conf->map.height = fd_to_lst(fd, &buf);
	size_check(conf);
	return (lst_to_array(buf, conf->map.height));
}

static void	char_pos_check(int x, int y, t_conf *conf)
{
	if (conf->map.map[y][x] == 'U')
	{
		conf->uni.pos_y = y;
		conf->uni.pos_x = x;
	}
	if (conf->map.map[y][x] == 'P')
	{
		conf->player.pos_y = y;
		conf->player.pos_x = x;
	}
	if (conf->map.map[y][x] == 'T')
	{
		conf->enemy.pos_y = y;
		conf->enemy.pos_x = x;
	}
}

void	pos_check(char **map, t_conf *conf)
{
	size_t		y;
	size_t		x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			char_pos_check(x, y, conf);
			x++;
		}
		y++;
	}
}

int	main(int ac, char **av)
{
	t_conf	conf;

	args_check(ac, av);
	initialize_conf(&conf);
	initialize_conf2(&conf);
	conf.map.map = map_set(av[1], &conf);
	map_check(conf.map.map, &conf);
	pos_check(conf.map.map, &conf);
	display_mlx(&conf);
	mlx_loop_hook(conf.mlx, animation, &conf);
	hook_loop_mlx(&conf);
}
