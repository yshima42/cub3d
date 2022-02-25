/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 00:24:18 by yshimazu          #+#    #+#             */
/*   Updated: 2022/02/25 14:38:07 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

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
	conf->map.n_enemies = 0;
	conf->map.n_unis = 0;
	conf->images.empty = NULL;
	conf->images.wall = NULL;
	conf->images.collectible = NULL;
	conf->images.exit = NULL;
	conf->images.player = NULL;
	conf->images.player2 = NULL;
	conf->images.player3 = NULL;
	conf->images.player4 = NULL;
	conf->images.player5 = NULL;
}

void	initialize_conf2(t_conf *conf)
{
	conf->images.enemy = NULL;
	conf->images.enemy2 = NULL;
	conf->images.uni = NULL;
	conf->images.size = TILE_SIZE;
	conf->player.pos_y = 0;
	conf->player.pos_x = 0;
	conf->player.n_steps = 0;
	conf->player.n_clicks = 0;
	conf->player.collectibles = 0;
	conf->enemy.pos_y = 0;
	conf->enemy.pos_x = 0;
	conf->uni.pos_y = 0;
	conf->uni.pos_x = 0;
}
