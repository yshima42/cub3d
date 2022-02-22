/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 12:15:34 by yshimazu          #+#    #+#             */
/*   Updated: 2021/08/11 12:15:34 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	if (!dest || !src)
		return (ft_strlen(dest) + ft_strlen(src));
	len = ft_strlen(dest);
	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (len + i < size - 1 && src[i] != 0)
	{
		dest[len + i] = src[i];
		i++;
	}
	dest[len + i] = '\0';
	if (size > len)
		size = len;
	return (size + ft_strlen(src));
}
