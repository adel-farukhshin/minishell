#include "builtins.h"
#include "executor.h"

int	save_fd(int fd[2])
{
	fd[STDIN_FILENO] = dup(STDIN_FILENO);
	if (fd[STDIN_FILENO] == -1)
		return (0);
	fd[STDOUT_FILENO] = dup(STDOUT_FILENO);
	if (fd[STDOUT_FILENO] == -1)
	{
		close(fd[STDIN_FILENO]);
		return (0);
	}
	return (1);
}

int	restore_fd(int fd[2])
{
	int	error;

	error = 0;
	if (dup2(fd[STDIN_FILENO], STDIN_FILENO) == -1)
		error = 1;
	if (dup2(fd[STDOUT_FILENO], STDOUT_FILENO) == -1)
		error = 1;
	if (error)
		return (0);
	return (1);
}

void	delete_saved_fd(int fd[2])
{
	if (fd[STDIN_FILENO] != -1)
		close(fd[STDIN_FILENO]);
	if (fd[STDOUT_FILENO] != -1)
		close(fd[STDOUT_FILENO]);
}

void	exe_one_builtin(t_node *cmd, t_context	*ctx, \
	t_shell	*shell, int builtin_num)
{
	int	fd[2];

	if (!save_fd(fd))
	{
		exit(1);
	}
	make_redir(cmd, ctx);
	start_buitins_parent(cmd, shell, builtin_num);
	if (!restore_fd(fd))
	{
		delete_saved_fd(fd);
		exit(1);
	}
	delete_saved_fd(fd);
}
