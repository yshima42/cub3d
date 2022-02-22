/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 00:22:39 by yshimazu          #+#    #+#             */
/*   Updated: 2021/10/03 00:22:41 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static void	enemy_step_to_next(char *current_pos, char *next_pos, t_conf *conf)
{
	(void)conf;
	if (next_pos_check(*next_pos, '0'))
		ft_swap(current_pos, next_pos);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

void	uni_move(int u_y, int u_x, t_conf *conf)
{
	int	dis_x;
	int	dis_y;

	dis_x = ft_abs(conf->player.pos_x - u_x);
	dis_y = ft_abs(conf->player.pos_y - u_y);
	if (dis_x >= dis_y)
	{
		if (conf->player.pos_x < u_x)
			enemy_step_to_next(&conf->map.map[u_y][u_x],
				&conf->map.map[u_y][u_x - 1], conf);
		else
			enemy_step_to_next(&conf->map.map[u_y][u_x],
				&conf->map.map[u_y][u_x + 1], conf);
	}
	else
	{
		if ((conf->player.pos_y < u_y))
			enemy_step_to_next(&conf->map.map[u_y][u_x],
				&conf->map.map[u_y - 1][u_x], conf);
		else
			enemy_step_to_next(&conf->map.map[u_y][u_x],
				&conf->map.map[u_y + 1][u_x], conf);
	}
}

void	enemy_move(int e_y, int e_x, t_conf *conf)
{
	conf->player.n_clicks++;
	if (conf->player.n_clicks % 6 < 3)
		enemy_step_to_next(&conf->map.map[e_y][e_x],
			&conf->map.map[e_y + 1][e_x], conf);
	else
		enemy_step_to_next(&conf->map.map[e_y][e_x],
			&conf->map.map[e_y - 1][e_x], conf);
}
