/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 22:03:22 by yshimazu          #+#    #+#             */
/*   Updated: 2022/02/23 20:40:12 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	array_to_screan(char **map, t_conf *conf)
{
	size_t	y;
	size_t	x;
	
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			conf->screen.img = chr_to_imgptr(map[y][x], conf);
			mlx_put_image_to_window(conf->mlx_ptr, conf->win_ptr, conf->screen.img,
				CHIP_SIZE * x, CHIP_SIZE * y);
			x++;
		}
		y++;
	}
}

void	display_mlx(t_conf *conf)
{
	int	size_x;
	int	size_y;

	chip_set(conf);
	size_y = (int)conf->map.height * CHIP_SIZE;
	size_x = (int)conf->map.width * CHIP_SIZE;
	if (conf->map.height > SCREEN_SIZE)
		size_y = SCREEN_SIZE * (CHIP_SIZE + 1);
	if (conf->map.width > SCREEN_SIZE)
		size_x = SCREEN_SIZE * (CHIP_SIZE + 1);
	array_to_screan(conf->map.map, conf);
}

int	expose(t_conf *conf)
{
	array_to_screan(conf->map.map, conf);
	return (0);
}

void	hook_loop_mlx(t_conf *conf)
{
	//mlx_hook(conf->win_ptr, 33, 1L << 17, free_all_exit, conf);
	mlx_hook(conf->win_ptr, 12, 1L << 15, expose, conf);
	mlx_loop(conf->mlx_ptr);
}
