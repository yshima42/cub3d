/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 22:03:22 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/03 18:33:41 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	array_to_screan(char **map, t_conf *conf)
{
	size_t	y;
	size_t	x;
	
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			conf->screen.img = chr_to_imgptr(map[y][x], conf);
			mlx_put_image_to_window(conf->mlx_ptr, conf->win_ptr, conf->screen.img,
				TILE_SIZE * x, TILE_SIZE * y);
			x++;
		}
		y++;
	}
}

void	display_mlx(t_conf *conf)
{
	int	size_x;
	int	size_y;

	chip_set(conf);
	size_y = (int)conf->map.height * TILE_SIZE;
	size_x = (int)conf->map.width * TILE_SIZE;
	if (conf->map.height > SCREEN_SIZE)
		size_y = SCREEN_SIZE * (TILE_SIZE + 1);
	if (conf->map.width > SCREEN_SIZE)
		size_x = SCREEN_SIZE * (TILE_SIZE + 1);
	array_to_screan(conf->map.map, conf);
}

int	free_all_exit(t_conf *conf)
{
	/* if (conf->map.map)
		conf->map.map = ft_arrayfree(conf->map.map);
	if (conf->images.empty)
		mlx_destroy_image(conf->mlx, conf->images.empty);
	if (conf->images.wall)
		mlx_destroy_image(conf->mlx, conf->images.wall);
	if (conf->images.collectible)
		mlx_destroy_image(conf->mlx, conf->images.collectible);
	if (conf->images.exit)
		mlx_destroy_image(conf->mlx, conf->images.exit);
	if (conf->images.player)
		mlx_destroy_image(conf->mlx, conf->images.player);
	if (conf->win_ptr)
		mlx_destroy_window(conf->mlx_ptr, conf->win_ptr);
	if (conf->mlx_ptr)
	{
		mlx_destroy_display(conf->mlx_ptr);
		mlx_loop_end(conf->mlx_ptr);
		free(conf->mlx_ptr);
	} */
	(void)conf;
	exit (EXIT_SUCCESS);
	return (0);
}

int	expose(t_conf *conf)
{
	render(conf);
	
	return (0);
}

void	hook_loop_mlx(t_conf *conf)
{
	mlx_hook(conf->win_ptr, 33, 1L << 17, free_all_exit, conf);
	mlx_hook(conf->win_ptr, 12, 1L << 15, expose, conf);
}
