/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 22:03:22 by yshimazu          #+#    #+#             */
/*   Updated: 2021/10/05 14:50:48 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static void	desplay_counter(t_conf *conf)
{
	char	*s_counter;

	s_counter = ft_itoa(conf->player.n_steps);
	mlx_string_put(conf->mlx, conf->win, 10, 20, 0xFFFFFF, s_counter);
	free(s_counter);
}

void	array_to_screan(char **map, t_conf *conf)
{
	void	*img_ptr;
	size_t	y;
	size_t	x;
	size_t	scroll_y;
	size_t	scroll_x;

	scroll_y = (conf->player.pos_y / SCREAN_SIZE) * SCREAN_SIZE;
	scroll_x = (conf->player.pos_x / SCREAN_SIZE) * SCREAN_SIZE;
	y = 0;
	while (map[y + scroll_y])
	{
		x = 0;
		while (map[y + scroll_y][x + scroll_x])
		{
			img_ptr = chr_to_imgptr(map[y + scroll_y][x + scroll_x], conf);
			mlx_put_image_to_window(conf->mlx, conf->win, img_ptr,
				CHIP_SIZE * x, CHIP_SIZE * y);
			x++;
		}
		y++;
	}
	desplay_counter(conf);
}

static int	key_hook(int keycode, t_conf *conf)
{
	if (keycode == W_KEY || keycode == A_KEY
		|| keycode == S_KEY || keycode == D_KEY)
		player_move(keycode, conf);
	if (keycode == ESC_KEY)
		free_all_exit(conf);
	pos_check(conf->map.map, conf);
	if (!(conf->player.pos_y % SCREAN_SIZE)
		|| !(conf->player.pos_x % SCREAN_SIZE))
		mlx_clear_window(conf->mlx, conf->win);
	array_to_screan(conf->map.map, conf);
	return (0);
}

void	display_mlx(t_conf *conf)
{
	int	size_y;
	int	size_x;

	conf->mlx = mlx_init();
	if (!conf->mlx)
		error_mlx(conf);
	chip_set(conf);
	chip_set2(conf);
	size_y = (int)conf->map.height * CHIP_SIZE;
	size_x = (int)conf->map.width * CHIP_SIZE;
	if (conf->map.height > SCREAN_SIZE)
		size_y = SCREAN_SIZE * (CHIP_SIZE + 1);
	if (conf->map.width > SCREAN_SIZE)
		size_x = SCREAN_SIZE * (CHIP_SIZE + 1);
	conf->win = mlx_new_window(conf->mlx, size_x,
			size_y, "so_long");
	if (!conf->mlx)
		error_mlx(conf);
	array_to_screan(conf->map.map, conf);
}

void	hook_loop_mlx(t_conf *conf)
{
	mlx_hook(conf->win, 2, 1L << 0, key_hook, conf);
	mlx_hook(conf->win, 33, 1L << 17, free_all_exit, conf);
	mlx_hook(conf->win, 12, 1L << 15, expose, conf);
	mlx_loop(conf->mlx);
}
