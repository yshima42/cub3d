/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:09:27 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/04 14:22:35 by yshimazu         ###   ########.fr       */
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

int	free_all_exit(t_conf *conf)
{
	if (conf->map.map)
		conf->map.map = ft_arrayfree(conf->map.map);
	if (conf->win_ptr)
		mlx_destroy_window(conf->mlx_ptr, conf->win_ptr);
	if (conf->mlx_ptr)
	{
		mlx_destroy_display(conf->mlx_ptr);
		mlx_loop_end(conf->mlx_ptr);
		free(conf->mlx_ptr);
	}
	mlx_destroy_display(&conf->screen);
	free(conf->color_buffer);
	exit(0);
}
