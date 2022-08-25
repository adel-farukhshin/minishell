
#include <stdlib.h>
#include "minishell.h"

void	ft_strncpy(char *dst, const char *src, long len)
{
	long	i;

	i = 0;
	while (src[i] && len > 0)
	{
		dst[i] = src[i];
		i++;
		len--;
	}
	dst[i] = '\0';
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r' || c == '\n')
		return (1);
	return (0);
}

// long	ft_strlen(const char *s)
// {
// 	long	a;

// 	a = 0;
// 	while (*s)
// 	{
// 		a++;
// 		s++;
// 	}
// 	return (a);
// }

char	*ft_strdup(const char *s1)
{
	char	*ret;
	char	*tmp;
	int		i;

	i = 0;
	ret = malloc(ft_strlen(s1) + 1);
	if (!ret)
		return (NULL);
	tmp = (char *) s1;
	while (*tmp)
		ret[i++] = *tmp++;
	ret[i] = '\0';
	return (ret);
}

char	*ft_strchr(const char *s, int c)
{
	char	a;
	char	*r;

	a = (char) c;
	r = (char *) s;
	while (*r)
	{
		if (*r == a)
		{
			return (r);
		}
		r++;
	}
	if (a == '\0')
		return (r);
	return (NULL);
}