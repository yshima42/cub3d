/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 00:21:10 by yshimazu          #+#    #+#             */
/*   Updated: 2021/10/05 14:51:27 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	chip_ani(int pos_y, int pos_x, void *img_ptr, t_conf *conf)
{
	size_t	scroll_y;
	size_t	scroll_x;

	scroll_y = (conf->player.pos_y / SCREAN_SIZE) * SCREAN_SIZE;
	scroll_x = (conf->player.pos_x / SCREAN_SIZE) * SCREAN_SIZE;
	mlx_put_image_to_window(conf->mlx, conf->win, img_ptr,
		CHIP_SIZE * (pos_x - scroll_x), CHIP_SIZE * (pos_y - scroll_y));
}

int	animation(t_conf *conf)
{
	static int	count;

	pos_check(conf->map.map, conf);
	count++;
	if (count == 5000)
	{
		chip_ani(conf->player.pos_y, conf->player.pos_x,
			conf->images.player, conf);
		chip_ani(conf->enemy.pos_y, conf->enemy.pos_x,
			conf->images.enemy, conf);
	}
	else if (count == 10000)
	{
		chip_ani(conf->player.pos_y, conf->player.pos_x,
			conf->images.player2, conf);
		chip_ani(conf->enemy.pos_y, conf->enemy.pos_x,
			conf->images.enemy2, conf);
	}
	if (count == 10000)
		count = 0;
	return (0);
}

int	expose(t_conf *conf)
{
	array_to_screan(conf->map.map, conf);
	return (0);
}
