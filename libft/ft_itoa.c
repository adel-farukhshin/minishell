/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 20:07:25 by mdaryn            #+#    #+#             */
/*   Updated: 2021/10/15 20:07:27 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_make_str(int length, int n, int negative_sign)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * length);
	if (!str)
		return (NULL);
	str[--length] = '\0';
	while (length--)
	{
		str[length] = n % 10 + '0';
		n = n / 10;
	}
	if (negative_sign)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		length;
	int		negative_sign;
	int		tmp;
	int		b;

	tmp = n;
	length = 2;
	negative_sign = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n *= -1;
		negative_sign = 1;
	}
	b = tmp / 10;
	while (b)
	{
		length++;
		b /= 10;
	}
	length += negative_sign;
	str = ft_make_str(length, n, negative_sign);
	return (str);
}
