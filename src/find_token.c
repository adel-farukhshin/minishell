
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

#include "scanner.h"
#include "minishell.h"

static char	find_key(char c);
static long	find_len(t_src *src, char key);
static long	redir_token(t_src *src, char *key);

t_token	*find_token(t_src *src)
// return: token; NULL: 1) EOF 2) error with quotes
{
	t_token	*tok;
	long	len;
	char	key;

	tok = NULL;
	len = 0;
	key = find_key(src->s[src->curpos]);
	if (!key)
		return (NULL);
	else if (key >= 1 && key <= 4)
		len = find_len(src, key);
	else if (key == 5)
		len = 0;
	else if (key == 6 || key == 7)
		len = redir_token(src, &key);
	if (len == -1)
		return (NULL);
	tok = create_token(key,
		src->s + src->curpos, len);
	if (!tok)
		return (NULL);
	src->curpos += len + 1;
	return (tok);
}

static char	find_key(char c)
{
	if (!c)
		return (0);
	else if (ft_isspace(c))
		return (1); // sep
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
		return (2); // word
}

static long	find_len(t_src *src, char key)
{
	long	len;
	char	tkey;

	len = 0;
	if (key == 1 || key == 2)
		while (find_key(src->s[src->curpos + ++len]) == key);
	else if (key == 3 || key == 4)
	{
		tkey = find_key(src->s[src->curpos + ++len]);
		while (tkey && tkey != key)
			tkey = find_key(src->s[src->curpos + ++len]);
		if (!tkey)
			return (-1);
		len++;
	}
	len--;
	return (len);
}

static long	redir_token(t_src *src, char *key)
{
	char	tkey;

	tkey = find_key(src->s[src->curpos + 1]);
	if (tkey == *key)
	{
		if (tkey == 6)
			*key = 8;
		else
			*key = 9;
		return (1);
	}
	return (0);
}
