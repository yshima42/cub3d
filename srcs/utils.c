/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:13:56 by yshimazu          #+#    #+#             */
/*   Updated: 2021/10/01 22:04:47 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	array_loop(char **map, t_conf *conf, char *f(char c, t_conf *conf))
{
	size_t	x;
	size_t	y;
	char	*error_message;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			error_message = f(map[y][x], conf);
			if (error_message)
				map_error_output(map, error_message);
			x++;
		}
		y++;
	}
}

int	ft_open_readfile(char *readfile)
{
	int	fd;

	fd = open(readfile, O_RDONLY);
	if (fd == -1)
		perror_exit("Open");
	return (fd);
}

char	**lst_to_array(t_list *buf, size_t height)
{
	t_list	*t_buf;
	size_t	i;
	char	**map;

	t_buf = buf;
	map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map)
		perror_exit("malloc");
	i = 0;
	while (t_buf)
	{
		map[i] = ft_strdup(t_buf->content);
		t_buf = t_buf->next;
		i++;
	}
	map[i] = NULL;
	ft_lstclear(&buf, free);
	return (map);
}

size_t	fd_to_lst(int fd, t_list **buf)
{
	char	*line;
	size_t	l_count;

	l_count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (l_count == 0)
			*buf = ft_lstnew(line);
		else
			ft_lstadd_back(buf, ft_lstnew(line));
		l_count++;
	}
	return (l_count);
}

void	ft_swap(char *a, char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
