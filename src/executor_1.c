#include "executor.h"

void	read_redirect(char *file_name, t_context *ctx)
{
	int	fd_in;

	fd_in = open(file_name, O_RDONLY);
	if (fd_in < 0)
	{
		ft_putstr_fd("minishell: No such file or directory: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	dup2(fd_in, ctx->fd[STDIN_FILENO]);
	close(fd_in);
}

void	write_redirect(char *file_name, int flag, t_context *ctx)
{
	int	fd_out;

	if (flag == 6)
		fd_out = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (flag == 8)
		fd_out = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		return ;
	dup2(fd_out, ctx->fd[STDOUT_FILENO]);
	close(fd_out);
}

int	make_redir(t_node	*cmd, t_context	*ctx)
{
	t_blist	*redir_list;

	redir_list = cmd->value.cmd_val.redirs;
	if (redir_list == NULL)
		return (0);
	while (redir_list)
	{
		if (*(char *)redir_list->key == R_OUT)
			write_redirect((char *)redir_list->val, R_OUT, ctx);
		if (*(char *)redir_list->key == R_IN || \
			*(char *)redir_list->key == R_INS)
		{
			read_redirect((char *)redir_list->val, ctx);
			if (*(char *)redir_list->key == R_INS)
			{
				unlink((char *)redir_list->val);
				free((char *)redir_list->val);
			}
		}
		if (*(char *)redir_list->key == R_APP)
			write_redirect((char *)redir_list->val, R_APP, ctx);
		redir_list = redir_list->next;
	}
	return (1);
}
