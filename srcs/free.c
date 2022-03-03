/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:09:27 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/03 15:06:59 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

/* int	free_all_exit(t_conf *conf)
{
	if (conf->map.map)
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
	if (conf->win)
		mlx_destroy_window(conf->mlx, conf->win);
	if (conf->mlx)
	{
		mlx_destroy_display(conf->mlx);
		mlx_loop_end(conf->mlx);
		free(conf->mlx);
	}
	exit (EXIT_SUCCESS);
	return (0);
}
 */