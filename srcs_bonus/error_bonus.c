/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:08:59 by yshimazu          #+#    #+#             */
/*   Updated: 2021/10/03 00:23:42 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

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
	ft_putstr_fd("Error\nSomething is wring in mlx function", 2);
	free_all_exit(conf);
}

static int	extension_check(char *filename)
{
	char	*dot_ptr;

	dot_ptr = ft_strchr(filename, '.');
	if (dot_ptr == NULL)
		return (-1);
	else
	{
		if (ft_strncmp(dot_ptr, ".ber\0", 5))
			return (-1);
	}
	return (0);
}

void	args_check(int ac, char **av)
{
	if (ac != 2 || extension_check(av[1]) == -1)
	{
		ft_putstr_fd("Error\nUsage: ./so_long xxx.ber\n", 2);
		exit (EXIT_SUCCESS);
	}
}
