/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 22:03:22 by yshimazu          #+#    #+#             */
/*   Updated: 2021/10/05 14:52:24 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	array_to_screan(char **map, t_conf *conf)
{
	void	*img_ptr;
	size_t	y;
	size_t	x;
	/* size_t	scroll_y;
	size_t	scroll_x;

	scroll_y = (conf->player.pos_y / SCREAN_SIZE) * SCREAN_SIZE;
	scroll_x = (conf->player.pos_x / SCREAN_SIZE) * SCREAN_SIZE; */
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			img_ptr = chr_to_imgptr(map[y][x], conf);
			mlx_put_image_to_window(conf->mlx, conf->win, img_ptr,
				CHIP_SIZE * x, CHIP_SIZE * y);
			x++;
		}
		y++;
	}
}

int	key_hook(int keycode, t_conf *conf)
{
	if (keycode == W_KEY || keycode == A_KEY
		|| keycode == S_KEY || keycode == D_KEY)
		player_move(keycode, conf);
	if (keycode == ESC_KEY)
		free_all_exit(conf);
	player_pos_check(conf->map.map, conf);
	if (!(conf->player.pos_y % SCREAN_SIZE)
		|| !(conf->player.pos_x % SCREAN_SIZE))
		mlx_clear_window(conf->mlx, conf->win);
	array_to_screan(conf->map.map, conf);
	return (0);
}

void	display_mlx(t_conf *conf)
{
	int	size_x;
	int	size_y;

	size_x = 1000;
	size_y = 1000;

	conf->mlx = mlx_init();
	if (!conf->mlx)
		error_mlx(conf);
	chip_set(conf);
	/* size_y = (int)conf->map.height * CHIP_SIZE;
	size_x = (int)conf->map.width * CHIP_SIZE;
	if (conf->map.height > SCREAN_SIZE)
		size_y = SCREAN_SIZE * (CHIP_SIZE + 1);
	if (conf->map.width > SCREAN_SIZE)
		size_x = SCREAN_SIZE * (CHIP_SIZE + 1); */
	conf->win = mlx_new_window(conf->mlx, size_x, size_y, "so_long");
	if (!conf->mlx)
		error_mlx(conf);
	array_to_screan(conf->map.map, conf);
}

int	expose(t_conf *conf)
{
	array_to_screan(conf->map.map, conf);
	return (0);
}

void	hook_loop_mlx(t_conf *conf)
{
	mlx_hook(conf->win, 2, 1L << 0, key_hook, conf);
	mlx_hook(conf->win, 33, 1L << 17, free_all_exit, conf);
	mlx_hook(conf->win, 12, 1L << 15, expose, conf);
	mlx_loop(conf->mlx);
}
