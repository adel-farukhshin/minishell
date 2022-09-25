/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:51:39 by mdaryn            #+#    #+#             */
/*   Updated: 2021/10/26 15:51:41 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "minishell.h" 

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
int		ft_strlen(const char *str);
// char	*ft_strchr(const char *s, int c);
char	*ft_new_strjoin(char *s1, char *s2);
char	*ft_read_str(int fd, char *read_str);
char	*ft_get_new_line(char	*read_str);
char	*ft_get_new_read_str(char *read_str);

#endif
