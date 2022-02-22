/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_action_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 00:29:04 by yshimazu          #+#    #+#             */
/*   Updated: 2021/10/03 22:47:00 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

int	next_pos_check(char next_pos_c, char check_c)
{
	if (next_pos_c == check_c)
		return (1);
	else
		return (0);
}

void	collect_item(char *a, char *b, t_conf *conf)
{
	*b = *a;
	*a = '0';
	conf->player.collectibles++;
}

static void	anime_loop(void *img1, void *img2, t_conf *conf)
{
	int	count;

	count = 0;
	while (++count < 15000)
		chip_ani(conf->player.pos_y, conf->player.pos_x,
			img1, conf);
	while (++count < 30000)
		chip_ani(conf->player.pos_y, conf->player.pos_x,
			img2, conf);
}

void	game_finish_animation(void *img1, void *img2, t_conf *conf)
{
	int	n_animation;

	n_animation = 0;
	if (!(conf->player.pos_y % SCREAN_SIZE)
		|| !(conf->player.pos_x % SCREAN_SIZE))
	{
		mlx_clear_window(conf->mlx, conf->win);
		array_to_screan(conf->map.map, conf);
	}
	while (++n_animation < 5)
		anime_loop(img1, img2, conf);
}
