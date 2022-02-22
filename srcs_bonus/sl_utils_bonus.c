/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:13:50 by yshimazu          #+#    #+#             */
/*   Updated: 2021/10/03 00:20:48 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	*chr_to_imgptr(char c, t_conf *conf)
{
	if (c == '0')
		return (conf->images.empty);
	else if (c == '1')
		return (conf->images.wall);
	else if (c == 'C')
		return (conf->images.collectible);
	else if (c == 'E')
		return (conf->images.exit);
	else if (c == 'P')
		return (conf->images.player);
	else if (c == 'T')
		return (conf->images.enemy);
	else if (c == 'U')
		return (conf->images.uni);
	else
	{
		ft_putstr_fd("Error\n", 2);
		free_all_exit(conf);
		return (NULL);
	}
}

void	chip_set(t_conf *conf)
{
	conf->images.empty = mlx_xpm_file_to_image(conf->mlx, IMG_EMPTY,
			&conf->images.size, &conf->images.size);
	if (!conf->images.empty)
		error_mlx(conf);
	conf->images.wall = mlx_xpm_file_to_image(conf->mlx, IMG_WALL,
			&conf->images.size, &conf->images.size);
	if (!conf->images.wall)
		error_mlx(conf);
	conf->images.collectible = mlx_xpm_file_to_image(conf->mlx, IMG_COLLECTIBLE,
			&conf->images.size, &conf->images.size);
	if (!conf->images.collectible)
		error_mlx(conf);
	conf->images.exit = mlx_xpm_file_to_image(conf->mlx, IMG_EXIT,
			&conf->images.size, &conf->images.size);
	if (!conf->images.exit)
		error_mlx(conf);
	conf->images.player = mlx_xpm_file_to_image(conf->mlx, IMG_PLAYER,
			&conf->images.size, &conf->images.size);
	if (!conf->images.player)
		error_mlx(conf);
	conf->images.player2 = mlx_xpm_file_to_image(conf->mlx, IMG_PLAYER_2,
			&conf->images.size, &conf->images.size);
	if (!conf->images.player2)
		error_mlx(conf);
}

void	chip_set2(t_conf *conf)
{
	conf->images.player3 = mlx_xpm_file_to_image(conf->mlx, IMG_PLAYER_3,
			&conf->images.size, &conf->images.size);
	if (!conf->images.player3)
		error_mlx(conf);
	conf->images.player4 = mlx_xpm_file_to_image(conf->mlx, IMG_PLAYER_4,
			&conf->images.size, &conf->images.size);
	if (!conf->images.player4)
		error_mlx(conf);
	conf->images.player5 = mlx_xpm_file_to_image(conf->mlx, IMG_PLAYER_5,
			&conf->images.size, &conf->images.size);
	if (!conf->images.player5)
		error_mlx(conf);
	conf->images.enemy2 = mlx_xpm_file_to_image(conf->mlx, IMG_ENEMY_2,
			&conf->images.size, &conf->images.size);
	if (!conf->images.enemy2)
		error_mlx(conf);
	conf->images.enemy = mlx_xpm_file_to_image(conf->mlx, IMG_ENEMY_1,
			&conf->images.size, &conf->images.size);
	if (!conf->images.enemy)
		error_mlx(conf);
	conf->images.uni = mlx_xpm_file_to_image(conf->mlx, IMG_UNICORN_1,
			&conf->images.size, &conf->images.size);
	if (!conf->images.uni)
		error_mlx(conf);
}

void	step_counter(t_conf *conf)
{
	conf->player.n_steps++;
	printf("Number of steps: %ld\n", conf->player.n_steps);
	if (conf->player.n_steps > SIZE_MAX)
	{
		ft_putstr_fd("Game Over: You walked way too much!!\n", 2);
		free_all_exit(conf);
	}
}

void	size_check(t_conf *conf)
{
	if (conf->map.width > INT32_MAX || conf->map.height > INT32_MAX)
		map_error_output(conf->map.map, "Map size is too big\n");
}
