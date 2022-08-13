#include <stdio.h>

#include <stdlib.h>

#include "parser.h"
#include "minishell.h" // utils

// #include "blists.h"
// #include "scanner.h"
// #include "minishell.h"

// NODE		::= CMD | PIPE
// CMD		::= SEP* + ARG + ARG* + [[R_OUT]* + [R_IN]* + [R_APPEND]* + [R_INSOURCE]*]* + [PIPE + CMD]*
// ARG		::= WORD | FIELD | EXT_FIELD
// PIPE		::= CMD + CMD

static t_node	*parse_cmd(t_l_list *t);
// @return: 0 - success; -1 error; -2 - arg was not found
static char		parse_arg(t_l_list *t, char **ret_val);
static t_node	*parse_pipe(t_l_list *t, t_node *cmd);

static void		skip_sep(t_l_list *t);

t_node *parse(t_l_list *token_list)
{
	t_node	*node;

	node = parse_cmd(token_list);
	return (node);
}

static t_node	*parse_cmd(t_l_list *t)
{
	t_node	*cmd;
	char	*arg;
	t_blist	*tok;

	arg = NULL;
	if (parse_arg(t, &arg) == -1)
		return (error_node_new("error in parsing argument"));
	else
		cmd = cmd_node_new(arg);
	
	// add args
	tok = ll_peek(t);
	while (ll_has_next(t) &&*(char *) tok->key >= WORD && *(char *) tok->key <= EXT_FIELD)
	{
		
		if (parse_arg(t, &arg) == 0)
		{
			if (cmd_add_arg(cmd, arg))
			{
				node_drop(cmd);
				return (error_node_new("error in adding argument"));
			}
		}
		else
		{
			node_drop(cmd);
			return (error_node_new("error in parsing argument"));
		}
		tok = ll_peek(t);
	}

	// parse_redir
	char	key;
	while (ll_has_next(t) &&*(char *) tok->key >= REDIR_OUT && *(char *) tok->key <= REDIR_INSOURCE)
	{
		key = *(char *)tok->key;
		tok = ll_take(t);
		if (parse_arg(t, &arg) == 0)
		{
			if (cmd_add_redir(cmd, arg, key))
			{
				node_drop(cmd);
				return (error_node_new("error in adding redir"));;
			}
		}
		else
		{
			node_drop(cmd);
			return (error_node_new("error in parsing redir"));
		}
		tok = ll_peek(t);
	}

	// Check for full null command
	if (!cmd->value.cmd_val.args->val &&
		!cmd->value.cmd_val.r_out &&
		!cmd->value.cmd_val.r_in &&
		!cmd->value.cmd_val.r_app &&
		!cmd->value.cmd_val.r_ins)
		return (error_node_new("error in command syntax"));

	// Parse pipe
	if (ll_has_next(t) && *(char *)tok->key == PIPE)
	{
		ll_take(t);
		cmd = parse_pipe(t, cmd);
	}
	
	return (cmd);

}

void skip_sep(t_l_list *t)
{
	t_blist	*next;

	next = ll_peek(t);
	if (ll_has_next(t) && *(char *)next->key == SEP)
		ll_take(t);
}

static char	parse_arg(t_l_list *t, char **ret_val)
{
	t_blist	*tok;
	char	*tmp_val;

	tmp_val = NULL;
	skip_sep(t);
	// loop args
	
	// concatenation
	
	tok = ll_peek(t);
	if (ll_has_next(t) && (*(char *)tok->key == WORD 
			|| *(char *)tok->key == FIELD || *(char *)tok->key == EXT_FIELD))
	{
		// extend
		if ((*(char *)tok->key == WORD || *(char *)tok->key == EXT_FIELD))
		{
			if (extend_arg(tok))
				return (-1);
		}
		tmp_val = ft_strdup(ll_take(t)->val);
	}
	else
		return (-2);
	skip_sep(t);
	*ret_val = tmp_val;
	return (0);
}

static t_node	*parse_pipe(t_l_list *t, t_node *cmd)
{
	t_node	*pipe;
	t_node	*next_cmd;

	next_cmd = parse_cmd(t);
	if (next_cmd->type == error_node)
	{
		node_drop(cmd);
		return (next_cmd);
	}
	pipe = pipe_node_new(cmd, next_cmd);
	if (!pipe)
	{
		node_drop(cmd);
		node_drop(next_cmd);
		return (error_node_new("error in allocating pipe"));
	}
	return (pipe);
}
