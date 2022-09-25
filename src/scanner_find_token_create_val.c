
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "scanner.h"
#include "minishell.h"

/**
 * @brief 
 * Allocates memory and copies the value of token.
 * 
 * @param val 
 * @param src 
 * @param key 
 * @param len 
 */

static void	val_cpy(char **val, t_src *src, char key, long len);

char	*create_val(t_src *src, char key)
{
	char	*val;
	long	len;	
	char	tkey;

	len = 0;
	if (key == SEP || key == WORD)
	{
		tkey = find_key(src->s[src->curpos + len++]);
		while (tkey == key)
			tkey = find_key(src->s[src->curpos + len++]);
		len -= 1;
	}
	else
	{
		src->curpos += 1;
		if (process_fields(src, key, &len))
			return (NULL);
	}
	val = NULL;
	val_cpy(&val, src, key, len);
	if (key == SEP || key == WORD)
		len -= 1;
	src->curpos += len;
	return (val);
}

static void	val_cpy(char **val, t_src *src, char key, long len)
{
	if (key == SEP)
		*val = malloc(sizeof(char) * (2));
	else
		*val = malloc(sizeof(char) * (len + 1));
	if (!(*val))
		return ;
	if (key == SEP)
		ft_strncpy(*val, " ", 1);
	else
		ft_strncpy(*val, src->s + src->curpos, len);
}
