/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 11:43:28 by mdaryn            #+#    #+#             */
/*   Updated: 2021/10/05 11:43:48 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	unsigned char	a;

	str = (unsigned char *) b;
	a = (unsigned char)c;
	while (len)
	{
		*str++ = a;
		len--;
	}
	return (b);
}
