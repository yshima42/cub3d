/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:13:46 by yshimazu          #+#    #+#             */
/*   Updated: 2021/10/03 00:29:47 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	player_move(int keycode, t_conf *conf)
{
	int	p_x;
	int	p_y;

	p_x = conf->player.pos_x;
	p_y = conf->player.pos_y;
	if (keycode == W_KEY || keycode == A_KEY
		|| keycode == S_KEY || keycode == D_KEY)
	{
		enemy_move(conf->enemy.pos_y, conf->enemy.pos_x, conf);
		uni_move(conf->uni.pos_y, conf->uni.pos_x, conf);
	}
	if (keycode == W_KEY)
		step_to_next(&conf->map.map[p_y][p_x],
			&conf->map.map[p_y - 1][p_x], conf);
	if (keycode == A_KEY)
		step_to_next(&conf->map.map[p_y][p_x],
			&conf->map.map[p_y][p_x - 1], conf);
	if (keycode == S_KEY)
		step_to_next(&conf->map.map[p_y][p_x],
			&conf->map.map[p_y + 1][p_x], conf);
	if (keycode == D_KEY)
		step_to_next(&conf->map.map[p_y][p_x],
			&conf->map.map[p_y][p_x + 1], conf);
}

void	game_complete(char *a, char *b, t_conf *conf)
{	
	if (conf->player.collectibles == conf->map.n_collectibles)
	{
		step_counter(conf);
		*b = *a;
		*a = '0';
		pos_check(conf->map.map, conf);
		array_to_screan(conf->map.map, conf);
		game_finish_animation(conf->images.player, conf->images.player5, conf);
		ft_putstr_fd("Game Clear!!\n", 1);
		free_all_exit(conf);
	}
}

static void	game_over(char *a, char *b, t_conf *conf)
{	
	*b = *a;
	*a = '0';
	step_counter(conf);
	pos_check(conf->map.map, conf);
	array_to_screan(conf->map.map, conf);
	game_finish_animation(conf->images.player3, conf->images.player4, conf);
	ft_putstr_fd("Game Over: You lost all coins!!\n", 1);
	free_all_exit(conf);
}

void	step_to_next(char *current_pos, char *next_pos, t_conf *conf)
{
	if (next_pos_check(*next_pos, 'C') || next_pos_check(*next_pos, '0'))
		step_counter(conf);
	if (next_pos_check(*next_pos, 'C'))
		collect_item(current_pos, next_pos, conf);
	else if (next_pos_check(*next_pos, 'E'))
		game_complete(current_pos, next_pos, conf);
	else if (next_pos_check(*next_pos, 'T'))
		game_over(current_pos, next_pos, conf);
	else if (next_pos_check(*next_pos, 'U'))
		game_over(current_pos, next_pos, conf);
	else if (next_pos_check(*next_pos, '0'))
		ft_swap(current_pos, next_pos);
}
