/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 22:03:22 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/04 00:19:57 by yshimazu         ###   ########.fr       */
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
			mlx_put_image_to_window(conf->mlx_ptr, conf->win_ptr,
				conf->screen.img, TILE_SIZE * x, TILE_SIZE * y);
			x++;
		}
		y++;
	}
}

/* void	display_mlx(t_conf *conf)
{
	int	size_x;
	int	size_y;

	chip_set(conf);
	size_y = (int)conf->map.height * TILE_SIZE;
	size_x = (int)conf->map.width * TILE_SIZE;
	if (conf->map.height > SCREEN_SIZE)
		size_y = SCREEN_SIZE * (TILE_SIZE + 1);
	if (conf->map.width > SCREEN_SIZE)
		size_x = SCREEN_SIZE * (TILE_SIZE + 1);
	array_to_screan(conf->map.map, conf);
} */

int	expose(t_conf *conf)
{
	render(conf);
	return (0);
}
