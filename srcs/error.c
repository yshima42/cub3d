/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:08:59 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/04 14:22:05 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	map_error_output(char **map, char *output)
{
	map = ft_arrayfree(map);
	ft_putstr_fd("Error\nMap: ", 2);
	ft_putstr_fd(output, 2);
	exit(EXIT_SUCCESS);
}

void	perror_exit(char *error_message)
{
	ft_putstr_fd("Error\n ", 2);
	perror(error_message);
	exit(EXIT_FAILURE);
}

void	error_mlx(t_conf *conf)
{
	(void)conf;
	ft_putstr_fd("Error\nSomething is wring in mlx function", 2);
	//free_all_exit(conf);
}

int	extension_check(char *filename)
{
	char	*dot_ptr;

	dot_ptr = ft_strchr(filename, '.');
	if (dot_ptr == NULL)
		return (-1);
	else
	{
		if (ft_strncmp(dot_ptr, ".cub\0", 5))
			return (-1);
	}
	return (0);
}

void	args_check(int ac, char **av)
{
	if (ac != 2 || extension_check(av[1]) == -1)
	{
		ft_putstr_fd("Error\nUsage: ./cub3d xxx.cub\n", 2);
		exit (EXIT_SUCCESS);
	}
}
