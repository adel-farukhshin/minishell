
#include <stdlib.h>
#include <unistd.h>

#include "scanner.h"
#include "minishell.h"

#include <stdio.h>

static int	data_cpy(t_token *tok, char key, char *val, long l);
void		free_token_list(t_token *head);

t_token	*tokenize(t_src *src)
{
	t_token	*head;
	t_token	*tok;
	t_token	*tmp;

	head = NULL;
	while (src->curpos < src->len)
	{
		tok = find_token(src);
		if (!tok)
		{
			free_token_list(head);
			return (NULL);
		}
		if (!head)
		{
			head = tok;
			tmp = tok;
		}
		else
		{
			tmp->next = tok;
			tmp = tok;
		}
	}
	return (head);
}

void	free_token_list(t_token *head)
{
	t_token	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head->next;
		free_token(head, 2);
		head = tmp;
	}
}

t_token	*create_token(char key, char *val, long l)
{
	t_token	*tok;
		
	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->key = malloc(sizeof(char));
	if (!tok->key)
	{
		free_token(tok, 0);
		return (NULL);
	}
	tok->val = NULL;
	tok->next = NULL;
	if (data_cpy(tok, key, val, l))
		return (NULL);
	return (tok);
}

static int	data_cpy(t_token *tok, char key, char *val, long l)
{
	*(char *)tok->key = key;
	if (key >= 2 && key <= 4)
	{	
		tok->val = malloc(sizeof(char) * l + 1);
		if (!tok->val)
		{
			free_token(tok, 1);
			return (-1);
		}
		if (key == 2)
			ft_strncpy(tok->val, val, l);
		else
			ft_strncpy(tok->val, val + 1, l - 2);
	}
	return (0);
}

void	free_token(t_token *tok, char m)
{
	if (m > 0 && tok->key)
		free(tok->key);
	if (m > 1 && tok->val)
		free(tok->val);
	free(tok);
}