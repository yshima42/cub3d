/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:08:36 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/04 14:40:22 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, size_t x, size_t y, t_color color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void
	squre_pixel_put(t_data *screen, t_xy_size_t pos, size_t size, t_color color)
{
	size_t	i;
	size_t	j;
	t_color	c_color;

	i = pos.x;
	while (i < pos.x + size)
	{
		j = pos.y;
		while (j < pos.y + size)
		{
			if (i == pos.x || j == pos.y)
				c_color = 0x808080;
			else
				c_color = color;
			my_mlx_pixel_put(screen, i, j, c_color);
			j++;
		}
		i++;
	}
}

void	rect_pixel_put(t_data *screen, t_xy_d start, t_rect rect, t_color color)
{
	size_t	i;
	size_t	j;

	i = start.y;
	while (i < start.y + rect.height)
	{
		j = start.x;
		while (j < start.x + rect.width)
		{
			my_mlx_pixel_put(screen, j, i, color);
			j++;
		}
		i++;
	}
}

void	circle_pixel_put(t_data *screen, t_xy_size_t pos,
	size_t radius, t_color color)
{
	size_t	x;
	size_t	y;
	size_t	dx;
	size_t	dy;

	y = pos.y - radius;
	while (y < pos.y + radius)
	{
		x = pos.x - radius;
		while (x < pos.x + radius)
		{
			dx = x - pos.x;
			dy = y - pos.y;
			if ((dx * dx) + (dy * dy) <= radius * radius)
			{
				my_mlx_pixel_put(screen, x, y, color);
			}
			x++;
		}
		y++;
	}
}
