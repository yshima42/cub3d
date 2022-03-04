/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:17:56 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/04 13:46:32 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/cub3d.h"

void	left_key(t_player *player)
{
	player->angle -= M_PI * ROTATE_SPEED;
	player->angle = normalize_angle(player->angle);
	player->pdx = cos(player->angle);
	player->pdy = sin(player->angle);
}

void	right_key(t_player *player)
{
	player->angle += M_PI * ROTATE_SPEED;
	player->angle = normalize_angle(player->angle);
	player->pdx = cos(player->angle);
	player->pdy = sin(player->angle);
}

void	esc_key(t_conf *conf)
{
	free_all_exit(conf);
}

int	deal_key(int key, t_conf *conf)
{
	if (key == A_KEY)
		a_key(conf->map, &conf->player);
	else if (key == D_KEY)
		d_key(conf->map, &conf->player);
	else if (key == W_KEY)
		w_key(conf->map, &conf->player);
	else if (key == S_KEY)
		s_key(conf->map, &conf->player);
	else if (key == LEFT_KEY)
		left_key(&conf->player);
	else if (key == RIGHT_KEY)
		right_key(&conf->player);
	else if (key == ESC_KEY)
		esc_key(conf);
	set_rays(conf);
	render(conf);
	return (0);
}
