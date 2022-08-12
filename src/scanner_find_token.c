
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

#include "scanner.h"
#include "minishell.h"

static char	find_key(char c);
// static long	find_len(t_src *src, char key);
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
	// printf("in find_token\n");
	key = find_key(src->s[src->curpos]);
	if (!key)
		return (NULL);
	else if (key >= 1 && key <= 4)
		val = create_val(src, key);
		// len = find_len(src, key);
	else if (key == 5)
		len = 0; // make zero; we do not read this field
	else if (key == 6 || key == 7)
		len = redir_token(src, &key);
	if (len == -1)
		return (NULL);
	tok = create_token(key, val, len);
	// printf("len after creating token is %ld\n", len);
	if (!tok)
		return (NULL);
	// src->curpos += len;
	src->curpos += 1;
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

static char	*create_val(t_src *src, char key)
{
	char	*val;
	long	len;	
	char	tkey;

	len = 0;
	if (key == SEP || key == WORD)
	{
		while (find_key(src->s[src->curpos + len++]) == key);
		len -= 1;			
	}
	else
	{
		src->curpos += 1;
		tkey = find_key(src->s[src->curpos + len]);
		while (tkey && tkey != key)
		{
			len++;
			tkey = find_key(src->s[src->curpos + len]);
		}
		if (!tkey)
			return (NULL);
	}
	val = NULL;
	val_cpy(&val, src, key, len);
	if (key == SEP || key == WORD)
		len -= 1;
	src->curpos += len;
	// printf("val is _%s_\nthe first char is_%c_\n", val, *(src->s + src->curpos));
	// update curpos
	return (val);
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

/*
static long	find_len(t_src *src, char key)
{
	long	len;
	char	tkey;

	len = 0;
	// printf("find_len: key is %d\n", key);
	// printf("cur: %s\n", src->s + src->curpos);
	if (key == 1 || key == 2)
		while (find_key(src->s[src->curpos + len++]) == key)
			;
			// printf("len: %ld\n", len);
	else if (key == 3 || key == 4)
	{
		src->curpos += 1;
		printf("ch before: %c\n", src->s[src->curpos + len]);
		tkey = find_key(src->s[src->curpos + len++]);
		printf("ch after: %c\n", src->s[src->curpos + len]);
		while (tkey && tkey != key)
			tkey = find_key(src->s[src->curpos + len++]);
		if (!tkey)
			return (-1);
		len++;
	}
	len--;
	// printf("exit find_len\n");
	return (len);
}
*/

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
