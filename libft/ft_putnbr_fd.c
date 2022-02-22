/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 12:15:15 by yshimazu          #+#    #+#             */
/*   Updated: 2021/08/11 12:15:16 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	n_usg;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n_usg = n * -1;
	}
	else
		n_usg = n;
	if (n_usg > 9)
		ft_putnbr_fd((n_usg / 10), fd);
	n_usg %= 10;
	ft_putchar_fd((char)n_usg + '0', fd);
}
