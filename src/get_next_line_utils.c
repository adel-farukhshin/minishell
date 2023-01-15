/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <mdaryn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:06:31 by mdaryn            #+#    #+#             */
/*   Updated: 2022/09/25 19:36:38 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_new_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
	{
		str[j++] = s2[i++];
	}
	str[j] = '\0';
	free(s1);
	return (str);
}

char	*ft_get_new_line(char	*read_str)
{
	char	*str;
	int		i;

	i = 0;
	if (read_str[i] == '\0')
		return (NULL);
	while (read_str[i] && read_str[i] != '\n')
		i++;
	str = (char *)malloc((i + 2) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (read_str[i] && read_str[i] != '\n')
	{
		str[i] = read_str[i];
		i++;
	}		
	if (read_str[i] && read_str[i] == '\n')
	{
		str[i] = read_str[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_get_new_read_str(char *read_str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	while (read_str[i] && read_str[i] != '\n')
		i++;
	if (!read_str[i])
	{
		free(read_str);
		return (NULL);
	}
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(read_str) - i + 1));
	if (!new_str)
		return (NULL);
	i++;
	j = 0;
	while (read_str[i])
		new_str[j++] = read_str[i++];
	new_str[j] = '\0';
	free(read_str);
	return (new_str);
}
