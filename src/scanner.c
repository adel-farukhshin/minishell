#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "scanner.h"
#include "minishell.h"

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

t_token	*create_token(char key, char *val)
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
	*(char *)tok->key = key;
	tok->val = val;
	return (tok);
}

void	free_token(t_token *tok, char m)
{
	if (m > 0 && tok->key)
		free(tok->key);
	if (m > 1 && tok->val)
		free(tok->val);
	free(tok);
}
