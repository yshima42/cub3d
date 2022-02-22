/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:10:18 by yshimazu          #+#    #+#             */
/*   Updated: 2021/09/30 16:10:19 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	initialize_conf(t_conf *conf)
{
	conf->mlx = NULL;
	conf->win = NULL;
	conf->map.map = NULL;
	conf->map.width = 0;
	conf->map.height = 0;
	conf->map.n_collectibles = 0;
	conf->map.n_players = 0;
	conf->map.n_exit = 0;
	conf->images.empty = NULL;
	conf->images.wall = NULL;
	conf->images.collectible = NULL;
	conf->images.exit = NULL;
	conf->images.player = NULL;
	conf->images.size = CHIP_SIZE;
	conf->player.pos_y = 0;
	conf->player.pos_x = 0;
	conf->player.n_steps = 0;
	conf->player.collectibles = 0;
}

void	map_check(char **map, t_conf *conf)
{
	rectangular_check(map, conf);
	wall_check(map, conf);
	array_loop(map, conf, invalid_char_check);
	array_loop(map, conf, inmap_char_count);
	n_char_check(map, conf);
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

void	player_pos_check(char **map, t_conf *conf)
{
	size_t		y;
	size_t		x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				conf->player.pos_y = y;
				conf->player.pos_x = x;
			}
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
	conf.map.map = map_set(av[1], &conf);
	map_check(conf.map.map, &conf);
	player_pos_check(conf.map.map, &conf);
	display_mlx(&conf);
	hook_loop_mlx(&conf);
}
