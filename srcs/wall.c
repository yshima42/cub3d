/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:08:51 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/03 23:50:20 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/cub3d.h"

void	set_ceiling_color(t_conf *conf, const t_3d info_3d, size_t *i)
{
	size_t	y;

	y = 0;
	while (y < info_3d.wall_top)
	{
		conf->color_buffer[(WINDOW_WIDTH * y) + *i] = 0xFF333333;
		y++;
	}
}

void	set_wall_color(t_conf *conf, const t_3d info_3d, size_t *i)
{
	size_t	y;

	y = info_3d.wall_top;
	while (y < info_3d.wall_bottom)
	{
		if (conf->rays[*i].was_hit_vertical)
			conf->color_buffer[(WINDOW_WIDTH * y) + *i] = 0xFFFFFFFF;
		else
			conf->color_buffer[(WINDOW_WIDTH * y) + *i] = 0xFFCCCCCC;
		y++;
	}
}

void	set_floor_color(t_conf *conf, const t_3d info_3d, size_t *i)
{
	size_t	y;

	y = info_3d.wall_bottom;
	while (y < WINDOW_HEIGHT)
	{
		conf->color_buffer[(WINDOW_WIDTH * y) + *i] = 0xFF777777;
		y++;
	}
}

void	render_3d_walls(t_conf *conf)
{
	size_t	i;	
	double	prep_distance;
	t_3d	info_3d;

	i = 0;
	while (i < NUM_RAYS)
	{
		prep_distance = conf->rays[i].distance
			* cos(conf->rays[i].angle - conf->player.angle);
		info_3d.wall_strip_height = (TILE_SIZE / prep_distance)
			* DIST_TO_PROJECTION;
		info_3d.wall_top = (WINDOW_HEIGHT / 2)
			- (info_3d.wall_strip_height / 2);
		if (info_3d.wall_top < 0)
			info_3d.wall_top = 0;
		info_3d.wall_bottom = (WINDOW_HEIGHT / 2)
			+ (info_3d.wall_strip_height / 2);
		if (info_3d.wall_bottom > WINDOW_HEIGHT)
			info_3d.wall_bottom = WINDOW_HEIGHT;
		set_ceiling_color(conf, info_3d, &i);
		set_wall_color(conf, info_3d, &i);
		set_floor_color(conf, info_3d, &i);
		i++;
	}
	render_color_buffer(conf);
}
