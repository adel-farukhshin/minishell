/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:55:33 by mdaryn            #+#    #+#             */
/*   Updated: 2021/10/11 19:55:37 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	size_t			needle_len;

	if (!len && !haystack && !needle)
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *) haystack);
	if ((needle_len > (size_t)ft_strlen(haystack)) || (len < 1))
		return (NULL);
	i = 0;
	while (i <= (len - needle_len))
	{
		if (ft_strncmp(haystack, needle, needle_len) == 0)
			return ((char *) haystack);
		haystack++;
		i++;
	}
	return (0);
}
