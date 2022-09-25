#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "minishell.h" // utils

static t_node	*parse_cmd(t_l_list *t, t_shell *sh);
static char		parse_redir(t_l_list *t, t_node *cmd, t_shell *sh);
static void		process_pipe(t_l_list *t, t_node **cmd, t_shell *sh);
static t_node	*parse_pipe(t_l_list *t, t_node *cmd, t_shell *sh);

t_node	*parse(t_l_list *token_list, t_shell *sh)
{
	t_node	*node;

	node = parse_cmd(token_list, sh);
	return (node);
}

static t_node	*parse_cmd(t_l_list *t, t_shell *sh)
{
	t_node	*cmd;
	char	*arg;
	char	ecode;

	arg = NULL;
	if (parse_arg(t, &arg, sh) == -1)
		return (error_node_new("error in parsing argument"));
	else
		cmd = cmd_node_new(arg);
	ecode = add_args(t, cmd, sh);
	if (ecode == 1)
		return (error_node_new("error in adding argument"));
	else if (ecode == 2)
		return (error_node_new("error in parsing argument"));
	ecode = parse_redir(t, cmd, sh);
	if (ecode == 1)
		return (error_node_new("error in adding redir"));
	else if (ecode == 2)
		return (error_node_new("error in parsing redir"));
	if (!cmd->value.cmd_val.args->val
		&& !cmd->value.cmd_val.redirs)
		return (error_node_new("error in command syntax"));
	process_pipe(t, &cmd, sh);
	return (cmd);
}

static char	parse_redir(t_l_list *t, t_node *cmd, t_shell *sh)
{
	char	*arg;
	t_blist	*tok;

	tok = ll_peek(t);
	while (ll_has_next(t) && *(char *) tok->key >= REDIR_OUT
		&& *(char *) tok->key <= REDIR_INSOURCE)
	{
		tok = ll_take(t);
		if (parse_arg(t, &arg, sh) == 0)
		{
			if (cmd_add_redir(cmd, arg, *(char *)tok->key))
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

static void	process_pipe(t_l_list *t, t_node **cmd, t_shell *sh)
{
	t_blist	*tok;

	tok = ll_peek(t);
	if (ll_has_next(t) && *(char *)tok->key == PIPE)
	{
		ll_take(t);
		*cmd = parse_pipe(t, *cmd, sh);
	}
}

static t_node	*parse_pipe(t_l_list *t, t_node *cmd, t_shell *sh)
{
	t_node	*pipe;
	t_node	*next_cmd;

	next_cmd = parse_cmd(t, sh);
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
