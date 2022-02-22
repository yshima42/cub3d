/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 12:29:28 by yshimazu          #+#    #+#             */
/*   Updated: 2021/09/25 15:44:45 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	buff_clear(t_gnl **s_buff, t_gnl *t_buff)
{
	t_gnl	*tmp;

	if (!s_buff || !(*s_buff))
		return ;
	if (*s_buff == t_buff)
	{
		*s_buff = t_buff->next;
		free(t_buff->memo);
		free(t_buff);
		return ;
	}
	tmp = *s_buff;
	while (tmp && (tmp->next != t_buff))
		tmp = tmp->next;
	tmp->next = t_buff->next;
	free(t_buff->memo);
	free(t_buff);
}

static int	line_output(t_gnl **t_buff, char *ptr, char **ret)
{
	char	*tmp;

	if (ptr)
	{
		*ret = ft_strndup((*t_buff)->memo, ptr - ((*t_buff)->memo));
		tmp = ft_strndup(ptr + 1, ft_strlen(ptr + 1));
		free((*t_buff)->memo);
		(*t_buff)->memo = tmp;
		return (SUCCESS);
	}
	else
	{
		if ((*t_buff)->memo && *((*t_buff)->memo) == '\0')
			*ret = NULL;
		else
		{
			*ret = ft_strndup((*t_buff)->memo, ft_strlen((*t_buff)->memo));
			tmp = ft_strndup("", 0);
			free((*t_buff)->memo);
			(*t_buff)->memo = tmp;
		}
		return (END_OF_FILE);
	}
}

static int	ft_getfd(t_gnl *t_buff, char *buff, char **ret)
{
	ssize_t	cc;
	char	*tmp;
	char	*ptr;

	ptr = NULL;
	while (1)
	{
		ptr = ft_strchr(t_buff->memo, '\n');
		if (ptr)
			break ;
		cc = read(t_buff->fd, buff, BUFFER_SIZE);
		if (cc == -1)
			return (ERROR);
		if (cc == 0)
			break ;
		buff[cc] = '\0';
		tmp = ft_strjoin(t_buff->memo, buff);
		free(t_buff->memo);
		t_buff->memo = tmp;
	}
	return (line_output(&t_buff, ptr, ret));
}

t_gnl	*ft_setlst(t_gnl **s_buff, int fd)
{
	t_gnl	*t_buff;

	if (!*s_buff)
	{
		t_buff = ft_gnlnew(fd, "");
		*s_buff = t_buff;
		return (t_buff);
	}
	t_buff = *s_buff;
	while (t_buff && t_buff->fd != fd)
		t_buff = t_buff->next;
	if (t_buff)
		return (t_buff);
	t_buff = ft_gnlnew(fd, "");
	t_buff->next = *s_buff;
	*s_buff = t_buff;
	return (t_buff);
}

char	*get_next_line(int fd)
{
	static t_gnl	*s_buff;
	t_gnl			*t_buff;
	char			*buff;
	int				status;
	char			*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	t_buff = ft_setlst(&s_buff, fd);
	buff = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	ret = NULL;
	status = ft_getfd(t_buff, buff, &ret);
	free(buff);
	if ((status == ERROR || status == END_OF_FILE))
		buff_clear(&s_buff, t_buff);
	if (status == ERROR)
		return (NULL);
	return (ret);
}
