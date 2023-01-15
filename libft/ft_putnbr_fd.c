/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:08:25 by mdaryn            #+#    #+#             */
/*   Updated: 2021/10/12 18:08:27 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_count_len(int num)
{
	int	a;
	int	len;

	len = 1;
	a = num;
	while (a / 10 > 0)
	{
		len *= 10;
		a /= 10;
	}
	return (len);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	num_len;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n == -2147483648)
	{
		ft_putchar_fd('2', fd);
		n = 147483648;
	}
	num_len = ft_count_len(n);
	while (num_len)
	{
		ft_putchar_fd(((n / num_len) + '0'), fd);
		n %= num_len;
		num_len /= 10;
	}
}
