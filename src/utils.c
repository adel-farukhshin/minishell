

void	ft_strcpy(char *dst, const char *src, long len)
{
	long	i;

	i = 0;
	while (src[i] && len >= 0)
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

long	ft_strlen(const char *s)
{
	long	a;

	a = 0;
	while (*s)
	{
		a++;
		s++;
	}
	return (a);
}
