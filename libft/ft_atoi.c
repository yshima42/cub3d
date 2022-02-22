/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 12:13:10 by yshimazu          #+#    #+#             */
/*   Updated: 2021/08/11 12:23:00 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*del_spaces(char const *str)
{
	char	*no_spaces_str;
	size_t	i;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	no_spaces_str = &((char *)str)[i];
	return (no_spaces_str);
}

static int	max_check(size_t result, char *ns_str, size_t i, int sign)
{
	size_t	temp;

	temp = result * 10 + (ns_str[i] - '0');
	if (temp / 10 != result)
	{
		if (sign == -1)
			return (0);
		else
			return (-1);
	}
	else
		return (1);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	size_t	result;
	char	*no_spaces_str;

	i = 0;
	result = 0;
	no_spaces_str = del_spaces(str);
	sign = 1;
	if (no_spaces_str[i] == '-' || no_spaces_str[i] == '+')
	{
		if (no_spaces_str[i] == '-')
			sign = -1;
		i++;
	}
	if (no_spaces_str[i] < '0' || no_spaces_str[i] > '9')
		return (0);
	while (no_spaces_str[i] >= '0' && no_spaces_str[i] <= '9')
	{
		if (max_check(result, no_spaces_str, i, sign) != 1)
			return (max_check(result, no_spaces_str, i, sign));
		result = result * 10 + (no_spaces_str[i] - '0');
		i++;
	}
	return ((int)result * sign);
}
