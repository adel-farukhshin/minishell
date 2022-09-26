#include "executor.h"
#include "clean.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

int	perror_cmd(t_shell *shell, char *cmd)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin("minishell", ": ");
	s2 = ft_strjoin(s1, cmd);
	free(s1);
	ft_putstr_fd(s2, 2);
	free(s2);
	ft_putstr_fd(": command not found\n", 2);
	shell->exit_status = CMD_NOT_FOUND;
	return (shell->exit_status);
}

void	exec_simple_cmd(t_node	*cmd, t_shell	*shell)
{
	char	*path_str;
	char	*exe_cmd;
	char	**cmd_paths;
	char	**cmd_args;

	path_str = find_path(shell->env_arr);
	cmd_paths = ft_split(path_str, ':');
	exe_cmd = get_cmd(cmd_paths, (char *)cmd->value.cmd_val.args->val);
	if (exe_cmd == NULL)
		exe_cmd = (char *)cmd->value.cmd_val.args->val;
	cmd_args = lst_to_char(&cmd->value.cmd_val.args);
	shell->exit_status = execve(exe_cmd, cmd_args, shell->env_arr);
	if (errno != 0)
	{
		if (shell->exit_status == -1)
			shell->exit_status = perror_cmd(shell, exe_cmd);
		exit(shell->exit_status);
	}
	clean_array(cmd_args);
	clean_array(cmd_paths);
	free(path_str);
	free(exe_cmd);
	exit(shell->exit_status);
}