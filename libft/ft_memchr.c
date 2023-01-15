/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:04:29 by mdaryn            #+#    #+#             */
/*   Updated: 2021/10/11 19:04:35 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	k;
	int				i;

	k = (unsigned char) c;
	str = (unsigned char *) s;
	i = 0;
	while (n--)
	{
		if (str[i] == k)
		{
			return (str + i);
		}
		i++;
	}
	return (0);
}
