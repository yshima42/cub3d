/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 12:15:21 by yshimazu          #+#    #+#             */
/*   Updated: 2021/10/01 22:02:18 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_all(char **dest, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(dest[j]);
		j++;
	}
	free(dest);
	return (NULL);
}

static char	*char_malloc(char const *src, char c, size_t i)
{
	size_t	len;
	char	*ptr;

	if (!src[0])
		return (0);
	len = 0;
	while (src[len] != c && src[len])
		len++;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (free_all(&ptr, i));
	return (ptr);
}

static size_t	line_count(char const *str, char c)
{
	size_t	one_before;
	size_t	count;

	count = 0;
	one_before = 1;
	while (*str)
	{
		if (one_before == 0 && *str == c)
			one_before = 1;
		if (one_before == 1 && *str != c)
		{
			count++;
			one_before = 0;
		}
		str++;
	}
	return (count);
}

char	**ft_split(char const *str, char c)
{
	char	**dest;
	size_t	num;
	size_t	i;
	size_t	j;

	if (!str)
		return (0);
	num = line_count(str, c);
	dest = (char **)malloc(sizeof(char *) * (num + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < num)
	{
		while (*str == c)
			str++;
		dest[i] = char_malloc(str, c, i);
		j = 0;
		while (*str != c && *str != '\0')
			dest[i][j++] = *str++;
		dest[i][j] = '\0';
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
