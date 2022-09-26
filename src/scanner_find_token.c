
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

#include "scanner.h"
#include "minishell.h"

t_token	*find_token(t_src *src)
{
	t_token	*tok;
	char	key;
	char	*val;

	tok = NULL;
	val = NULL;
	key = find_key(src->s[src->curpos]);
	if (!key)
		return (NULL);
	else if (key >= 1 && key <= 4)
	{
		val = create_val(src, key);
		if (!val)
			return (NULL);
	}
	else if (key == 6 || key == 7)
		redir_token(src, &key);
	tok = create_token(key, val);
	if (!tok)
		return (NULL);
	src->curpos += 1;
	return (tok);
}

char	find_key(char c)
{
	if (!c)
		return (0);
	else if (ft_isspace(c))
		return (1);
	else if (c == '\'')
		return (3);
	else if (c == '\"')
		return (4);
	else if (c == '|')
		return (5);
	else if (c == '>')
		return (6);
	else if (c == '<')
		return (7);
	else
		return (2);
}

char	process_fields(t_src *src, char key, long *len)
{
	char	tkey;
	long	l;

	l = *len;
	tkey = find_key(src->s[src->curpos + l]);
	while (tkey && tkey != key)
	{
		l++;
		tkey = find_key(src->s[src->curpos + l]);
	}
	*len = l;
	if (!tkey)
		return (1);
	return (0);
}

long	redir_token(t_src *src, char *key)
{
	char	tkey;

	tkey = find_key(src->s[src->curpos + 1]);
	if (tkey == *key)
	{
		src->curpos += 1;
		if (tkey == 6)
			*key = 8;
		else
			*key = 9;
		return (2);
	}
	return (1);
}
