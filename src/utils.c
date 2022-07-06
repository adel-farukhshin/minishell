

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