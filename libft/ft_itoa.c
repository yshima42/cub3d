/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 12:13:43 by yshimazu          #+#    #+#             */
/*   Updated: 2021/08/11 12:13:43 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_getsize(long n_long)
{
	size_t	size;

	size = 0;
	if (n_long < 0)
		size++;
	while (n_long / 10)
	{
		size++;
		n_long = n_long / 10;
	}
	size++;
	return (size);
}

char	*ft_itoa(int n)
{
	char	*ans;
	long	n_long;
	size_t	size;

	n_long = n;
	size = ft_getsize(n_long);
	ans = (char *)malloc(sizeof(char) * (size + 1));
	if (!ans)
		return (NULL);
	if (n_long < 0)
	{
		ans[0] = '-';
		n_long = -n_long;
	}
	if (n_long == 0)
		ans[0] = '0';
	ans[size] = '\0';
	size--;
	while (n_long > 0)
	{
		ans[size] = n_long % 10 + '0';
		n_long /= 10;
		size--;
	}
	return (ans);
}
