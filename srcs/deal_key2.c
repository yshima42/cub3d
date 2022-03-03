/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:33:35 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/04 00:21:35 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/cub3d.h"

void	a_key(t_map map, t_player *player)
{
	double	left_angle;

	left_angle = normalize_angle(player->angle - M_PI / 2);
	move_player(map, player,
		player->pos.x + PLAYER_SIZE * cos(left_angle),
		player->pos.y + PLAYER_SIZE * sin(left_angle)
		);
}

void	d_key(t_map map, t_player *player)
{
	double	right_angle;

	right_angle = normalize_angle(player->angle + M_PI / 2);
	move_player(map, player,
		player->pos.x + PLAYER_SIZE * cos(right_angle),
		player->pos.y + PLAYER_SIZE * sin(right_angle)
		);
}

void	w_key(t_map map, t_player *player)
{
	move_player(map, player,
		player->pos.x + PLAYER_SIZE * cos(player->angle),
		player->pos.y + PLAYER_SIZE * sin(player->angle)
		);
}

void	s_key(t_map map, t_player *player)
{
	move_player(map, player,
		player->pos.x - PLAYER_SIZE * cos(player->angle),
		player->pos.y - PLAYER_SIZE * sin(player->angle)
		);
}
