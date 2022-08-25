/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:46:03 by mdaryn            #+#    #+#             */
/*   Updated: 2021/10/11 18:46:11 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	k;

	k = (char)c;
	str = (char *) s + ft_strlen(s);
	if (!s)
		return (0);
	while (str >= s)
	{
		if (*str == k)
		{
			return (str);
		}
		str--;
	}
	return (0);
}
