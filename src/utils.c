

void	ft_strcpy(char *dst, const char *src, long len)
{
	long	i;

	i = 0;
	while (src[i] && len)
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