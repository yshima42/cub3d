/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:08:49 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/04 00:57:56 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/cub3d.h"

void
	move_player(const t_map map, t_player *player, double new_x, double new_y)
{
	if (!has_wall_at(map, new_x, new_y))
	{
		player->pos.x = new_x;
		player->pos.y = new_y;
	}
}

void	render_player(t_data *screen, const t_player player)
{
	t_xy_size_t	mini_pos;

	mini_pos.x = player.pos.x;
	mini_pos.y = player.pos.y;
	circle_pixel_put(screen, mini_pos,
		PLAYER_SIZE / 2, 0x00FF0000);
	line_pixel_put(screen, mini_pos, player.angle, 30, 0x00FF0000);
}
