#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "minishell.h"

static void		skip_sep(t_l_list *t);
char			save_arg(t_l_list *t, t_list **val_list);

char	parse_arg(t_l_list *t, char **ret_val, t_shell *sh)
{
	t_list	*val_list;
	t_blist	*tok;

	val_list = NULL;
	skip_sep(t);
	tok = ll_peek(t);
	if (!ll_has_next(t) || (*(char *)tok->key != WORD
			&& *(char *)tok->key != FIELD && *(char *)tok->key != EXT_FIELD))
		return (-2);
	while (ll_has_next(t) && (*(char *)tok->key == WORD
			|| *(char *)tok->key == FIELD || *(char *)tok->key == EXT_FIELD))
	{
		if ((*(char *)tok->key == WORD || *(char *)tok->key == EXT_FIELD))
		{
			if (extend_arg(tok, sh))
				return (-1);
		}
		if (save_arg(t, &val_list) == -1)
			return (-1);
		tok = ll_peek(t);
	}
	skip_sep(t);
	*ret_val = str_join(val_list);
	lst_clear(&val_list, free);
	return (0);
}

static void	skip_sep(t_l_list *t)
{
	t_blist	*next;

	next = ll_peek(t);
	if (ll_has_next(t) && *(char *)next->key == SEP)
		ll_take(t);
}

char	save_arg(t_l_list *t, t_list **val_list)
{
	t_blist	*tok;
	t_list	*n;
	char	*tmp_val;

	tmp_val = NULL;
	tok = ll_take(t);
	tmp_val = ft_strdup(tok->val);
	if (!tmp_val)
	{
		lst_clear(val_list, free);
		return (-1);
	}
	tok = ll_peek(t);
	n = lst_new(tmp_val);
	if (!n)
	{
		lst_clear(val_list, free);
		return (-1);
	}
	lst_add_back(val_list, n);
	return (0);
}

char	add_args(t_l_list *t, t_node *cmd, t_shell *sh)
{
	char	*arg;
	t_blist	*tok;

	tok = ll_peek(t);
	while (ll_has_next(t) && *(char *) tok->key >= WORD
		&& *(char *) tok->key <= EXT_FIELD)
	{
		if (parse_arg(t, &arg, sh) == 0)
		{
			if (cmd_add_arg(cmd, arg))
			{
				node_drop(cmd);
				return (1);
			}
		}
		else
		{
			node_drop(cmd);
			return (2);
		}
		tok = ll_peek(t);
	}
	return (0);
}
