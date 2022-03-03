/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 00:01:50 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/04 00:02:34 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/cub3d.h"

void	print_pos(t_player player)
{
	printf("x: %f\n", player.pos.x);
	printf("y: %f\n", player.pos.y);
}

void	print_angle(t_conf *conf)
{
	printf("angle: %f\n", conf->player.angle);
	printf("pdx: %f\n", conf->player.pdx);
	printf("pdy: %f\n", conf->player.pdy);
}

/* void	print_array(t_conf *conf)
{
	for (size_t y = 0; y < conf->map.width; y++)
		for (size_t x = 0; x < conf->map.height; x++)
			printf("%c\n", conf->map.map[y][x]);
} */
