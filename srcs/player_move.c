/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:13:46 by yshimazu          #+#    #+#             */
/*   Updated: 2021/09/30 16:13:47 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	player_move(int keycode, t_conf *conf)
{
	int	x;
	int	y;

	x = conf->player.pos_x;
	y = conf->player.pos_y;
	if (keycode == W_KEY)
		step_to_next(&conf->map.map[y][x], &conf->map.map[y - 1][x], conf);
	if (keycode == A_KEY)
		step_to_next(&conf->map.map[y][x], &conf->map.map[y][x - 1], conf);
	if (keycode == S_KEY)
		step_to_next(&conf->map.map[y][x], &conf->map.map[y + 1][x], conf);
	if (keycode == D_KEY)
		step_to_next(&conf->map.map[y][x], &conf->map.map[y][x + 1], conf);
}

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

void	game_complete(char *a, char *b, t_conf *conf)
{	
	if (conf->player.collectibles == conf->map.n_collectibles)
	{
		step_counter(conf);
		*b = *a;
		*a = '0';
		ft_putstr_fd("Game Clear!!\n", 1);
		free_all_exit(conf);
	}
}

void	step_to_next(char *current_pos, char *next_pos, t_conf *conf)
{
	if (next_pos_check(*next_pos, 'C') || next_pos_check(*next_pos, '0'))
		step_counter(conf);
	if (next_pos_check(*next_pos, 'C'))
		collect_item(current_pos, next_pos, conf);
	else if (next_pos_check(*next_pos, 'E'))
		game_complete(current_pos, next_pos, conf);
	else if (next_pos_check(*next_pos, '0'))
		ft_swap(current_pos, next_pos);
}
