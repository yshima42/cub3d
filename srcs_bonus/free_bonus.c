/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:09:27 by yshimazu          #+#    #+#             */
/*   Updated: 2021/10/05 14:51:58 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

char	**ft_arrayfree(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	return (NULL);
}

void	free_mlx_win(t_conf *conf)
{
	if (conf->images.uni)
		mlx_destroy_image(conf->mlx, conf->images.uni);
	if (conf->win)
		mlx_destroy_window(conf->mlx, conf->win);
	if (conf->mlx)
	{
		mlx_destroy_display(conf->mlx);
		mlx_loop_end(conf->mlx);
		free(conf->mlx);
	}
}

void	free_chip1(t_conf *conf)
{
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
	if (conf->images.player2)
		mlx_destroy_image(conf->mlx, conf->images.player2);
	if (conf->images.player3)
		mlx_destroy_image(conf->mlx, conf->images.player3);
	if (conf->images.player4)
		mlx_destroy_image(conf->mlx, conf->images.player4);
	if (conf->images.player5)
		mlx_destroy_image(conf->mlx, conf->images.player5);
}

void	free_chip2(t_conf *conf)
{
	if (conf->images.enemy)
		mlx_destroy_image(conf->mlx, conf->images.enemy);
	if (conf->images.enemy2)
		mlx_destroy_image(conf->mlx, conf->images.enemy2);
}

int	free_all_exit(t_conf *conf)
{
	if (conf->map.map)
		conf->map.map = ft_arrayfree(conf->map.map);
	free_chip1(conf);
	free_chip2(conf);
	free_mlx_win(conf);
	exit (EXIT_SUCCESS);
	return (0);
}
