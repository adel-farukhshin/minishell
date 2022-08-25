/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:25:08 by mdaryn            #+#    #+#             */
/*   Updated: 2021/10/08 15:25:11 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*new_src;
	unsigned char	*new_dst;

	if (!dst && !src)
		return (0);
	new_src = (unsigned char *) src;
	new_dst = (unsigned char *) dst;
	while (n)
	{
		*new_dst++ = *new_src++;
		n--;
	}
	return (dst);
}
