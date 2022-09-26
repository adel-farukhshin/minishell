/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <mdaryn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:43:18 by mdaryn            #+#    #+#             */
/*   Updated: 2022/09/26 19:04:59 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "clean.h"

void	exec_one_cmd(t_node *cmd, t_context	*ctx, t_shell	*shell)
{
	int			children;
	int			builtin_num;
	int			status;
	int			i;

	i = 0;
	builtin_num = check_builtins(cmd);
	if (builtin_num != BUILTIN_NONE)
		exe_one_builtin(cmd, ctx, shell, builtin_num);
	else
	{
		children = execute_cmd(cmd, ctx, shell);
		while (i < children)
		{
			wait(&status);
			shell->exit_status = WEXITSTATUS(status);
			i++;
		}
	}
}

int	executor(t_node *cmd, t_shell	*shell)
{
	t_context	ctx;
	int			children;
	int			i;
	int			status;

	i = 0;
	ctx.fd[0] = STDIN_FILENO;
	ctx.fd[1] = STDOUT_FILENO;
	ctx.fd_close = -1;
	checking_heredoc(cmd, shell);
	if (cmd->type == cmd_node)
		exec_one_cmd(cmd, &ctx, shell);
	else
	{
		children = exec_node(cmd, &ctx, shell);
		while (i < children)
		{
			wait(&status);
			shell->exit_status = WEXITSTATUS(status);
			i++;
		}
	}
	return (children);
}

int	exec_node(t_node	*cmd, t_context	*ctx, t_shell	*shell)
{
	int	children;

	children = 0;
	if (cmd->type == error_node)
	{
		printf("error: %s\n", cmd->value.error_msg);
		return (0);
	}
	else if (cmd->type == cmd_node)
		return (execute_cmd(cmd, ctx, shell));
	else
		return (execute_pipe(cmd, ctx, shell, &children));
}

int	execute_cmd(t_node	*cmd, t_context	*ctx, t_shell	*shell)
{
	pid_t	pid;
	int		builtin_num;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		make_redir(cmd, ctx);
		dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO);
		dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO);
		if (ctx->fd_close >= 0)
			close(ctx->fd_close);
		builtin_num = check_builtins(cmd);
		if (builtin_num == BUILTIN_NONE)
			exec_simple_cmd(cmd, shell);
		else
			start_buitins_child(cmd, shell, builtin_num);
	}
	return (1);
}

int	execute_pipe(t_node	*cmd, t_context	*ctx, t_shell	*shell, int *children)
{
	t_node		*left;
	t_node		*right;
	int			ft_pipe[2];
	t_context	left_ctx;
	t_context	right_ctx;

	pipe(ft_pipe);
	left = cmd->value.pipe_val.left;
	left_ctx = *ctx;
	left_ctx.fd[STDOUT_FILENO] = ft_pipe[STDOUT_FILENO];
	left_ctx.fd_close = ft_pipe[STDIN_FILENO];
	*children += exec_node(left, &left_ctx, shell);
	close(ft_pipe[STDOUT_FILENO]);
	right = cmd->value.pipe_val.right;
	right_ctx = *ctx;
	right_ctx.fd[STDIN_FILENO] = ft_pipe[STDIN_FILENO];
	right_ctx.fd_close = ft_pipe[STDOUT_FILENO];
	*children += exec_node(right, &right_ctx, shell);
	close(ft_pipe[STDIN_FILENO]);
	return (*children);
}
