/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:03:17 by mdaryn            #+#    #+#             */
/*   Updated: 2021/10/08 17:03:24 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*new_src;
	unsigned char	*new_dst;

	if (!dst && !src)
		return (0);
	new_src = (unsigned char *) src;
	new_dst = (unsigned char *) dst;
	if (new_dst < new_src)
	{
		while (len--)
			*new_dst++ = *new_src++;
	}
	else
	{
		new_dst += len;
		new_src += len;
		while (len--)
		{
			*--new_dst = *--new_src;
		}
	}
	return (dst);
}
