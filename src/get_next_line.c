/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:57:39 by mdaryn            #+#    #+#             */
/*   Updated: 2021/10/26 15:57:45 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_str(int fd, char *read_str)
{
	char	*buff;
	int		reading_bytes;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	reading_bytes = 1;
	while (!ft_strchr(read_str, '\n') && reading_bytes != 0)
	{
		reading_bytes = read(fd, buff, BUFFER_SIZE);
		if (reading_bytes == -1)
		{
			free(buff);
			read_str = NULL;
			return (NULL);
		}
		buff[reading_bytes] = '\0';
		read_str = ft_new_strjoin(read_str, buff);
	}
	free(buff);
	return (read_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*read_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_str = ft_read_str(fd, read_str);
	if (read_str == NULL)
		return (NULL);
	line = ft_get_new_line(read_str);
	read_str = ft_get_new_read_str(read_str);
	return (line);
}
