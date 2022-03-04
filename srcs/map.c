/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:08:46 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/04 00:57:27 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/cub3d.h"

bool	has_wall_at(t_map map, double x, double y)
{
	size_t	map_x;
	size_t	map_y;

	if (x < 0 || x >= map.width * TILE_SIZE
		|| y < 0 || y >= map.height * TILE_SIZE)
		return (true);
	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	return (map.map[map_y][map_x] != '0');
}

bool	is_inside_map(t_map map, double x, double y)
{
	return (x >= 0 && x <= map.width * TILE_SIZE
		&& y >= 0 && y <= map.height * TILE_SIZE);
}

void	render_map(t_data *screen, char **map)
{
	size_t		y;
	size_t		x;
	t_xy_size_t	mini_pos;
	color_t		tile_color;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0')
				tile_color = 0x000000;
			else
				tile_color = 0xFFFFFFFF;
			mini_pos.x = x * TILE_SIZE;
			mini_pos.y = y * TILE_SIZE;
			squre_pixel_put(screen, mini_pos,
				TILE_SIZE, tile_color);
			x++;
		}
		y++;
	}
}
