
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

#include "scanner.h"
#include "minishell.h"

static char	find_key(char c);
static long	redir_token(t_src *src, char *key);

/**
 * @brief 
 * Creates a val. Updates curpos, so it equals the last character of token. 
 * Returns token's value or null (in case of error).
 * 
 * @param src 
 * @param key 
 * @return char* 
 */

/**
 * @brief 
 * Parses fields. Returns 0 on success and 1 on failure.
 * 
 * @param src 
 * @param key 
 * @param len 
 * @return char 
 */
char	process_fields(t_src *src, char key, long *len);

static char	*create_val(t_src *src, char key);
/**
 * @brief 
 * Allocates memory and copies the value of token.
 * 
 * @param val 
 * @param src 
 * @param key 
 * @param len 
 */

static void val_cpy(char **val, t_src *src, char key, long len);


t_token	*find_token(t_src *src)
// return: token; NULL: 1) EOF 2) error with quotes
{
	t_token	*tok;
	long	len;
	char	key;
	char	*val;

	tok = NULL;
	len = 0;
	key = find_key(src->s[src->curpos]);
	if (!key)
		return (NULL);
	else if (key >= 1 && key <= 4)
		val = create_val(src, key);
	else if (key == 5)
		len = 0;
	else if (key == 6 || key == 7)
		len = redir_token(src, &key);
	if (len == -1)
		return (NULL);
	tok = create_token(key, val);
	if (!tok)
		return (NULL);
	src->curpos += 1;
	return (tok);
}

static char	find_key(char c)
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

static char	*create_val(t_src *src, char key)
{
	char	*val;
	long	len;	

	len = 0;
	if (key == SEP || key == WORD)
	{
		while (find_key(src->s[src->curpos + len++]) == key);
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

static void val_cpy(char **val, t_src *src, char key, long len)
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
		return (2);
	}
	return (1);
}
