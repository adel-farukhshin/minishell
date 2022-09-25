#ifndef EXECUTOR_H
# define EXECUTIR_H
# include "minishell.h"
# include "node.h"
# include <fcntl.h>
# include "lists.h"
# include "builtins.h"
# include <errno.h>

int		exec_node(t_node	*cmd, t_context	*ctx, t_shell	*shell);
int		execute_cmd(t_node	*cmd, t_context	*ctx, t_shell	*shell);
int		execute_pipe(t_node	*cmd, t_context	*ctx, t_shell	*shell, \
	int *children);
int		executor(t_node	*cmd, t_shell	*shell);
void	exec_simple_cmd(t_node	*cmd, t_shell	*shell);
int		make_redir(t_node	*cmd, t_context *ctx);
void	read_redirect(char	*file_name, t_context	*ctx);
void	write_redirect(char *file_name, int flag, t_context *ctx);
void	checking_heredoc(t_node	*cmd);
char	*get_next_line(int fd);
#endif