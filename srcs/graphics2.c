/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:08:41 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/04 13:43:43 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/cub3d.h"

void	clear_color_buffer(t_conf *conf, t_color color)
{
	size_t	i;

	i = 0;
	while (i < WINDOW_WIDTH * WINDOW_HEIGHT)
	{
		conf->color_buffer[i] = color;
		i++;
	}
}

void	render_color_buffer(t_conf *conf)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			my_mlx_pixel_put(&conf->screen, x, y,
				conf->color_buffer[(WINDOW_WIDTH * y) + x]);
			y++;
		}
		x++;
	}
}

void	line_pixel_put(t_data *screen, t_xy_size_t pos, double angle, double len, t_color color)
{
	size_t	x;
	size_t	y;
	double	i;

	i = 0;
	while (i < len)
	{
		x = pos.x + i * cos(angle);
		y = pos.y + i * sin(angle);
		my_mlx_pixel_put(screen, x, y, color);
		i++;
	}
}

void
	line_pixel_put_2(t_data *screen, t_xy_d start, t_xy_d end, t_color color)
{
	t_xy_d	line;
	t_xy_d	delta;
	size_t	len;
	double	rad;
	size_t	i;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	len = sqrt(delta.x * delta.x + delta.y * delta.y);
	rad = atan2(delta.y, delta.x);
	i = 0;
	while (i < len)
	{
		line.x = start.x + i * cos(rad);
		line.y = start.y + i * sin(rad);
		my_mlx_pixel_put(screen, round(line.x), round(line.y), color);
		i++;
	}
}

//there is bug I think (some lines come)
void
	line_pixel_put_3(t_data *screen, t_xy_d start, t_xy_d end, t_color color)
{
	t_xy_d	inc;
	t_xy_d	delta;
	size_t	side_len;
	size_t	i;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	if (fabs(delta.x) >= fabs(delta.y))
		side_len = fabs(delta.x);
	else
		side_len = fabs(delta.y);
	inc.x = delta.x / (double)side_len;
	inc.y = delta.y / (double)side_len;
	i = 0;
	while (i <= side_len)
	{
		my_mlx_pixel_put(screen, start.x, start.y, color);
		start.x += inc.x;
		start.y += inc.y;
		i++;
	}
}
