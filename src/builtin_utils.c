#include "builtins.h"
#include "executor.h"
#include "clean.h"

void	start_buitins_parent(t_node	*cmd, t_shell	*shell, int builtin_num)
{
	char	**cmd_args;
	char	*cmd_str;

	cmd_str = (char *)cmd->value.cmd_val.args->val;
	if (cmd_str != NULL)
	{
		cmd_args = lst_to_char(&cmd->value.cmd_val.args);
		if (builtin_num == BUILTIN_CD)
			cd_cmd(shell, cmd_args);
		if (builtin_num == BUILTIN_EXIT)
			exit_cmd(shell, cmd_args);
		if (builtin_num == BUILTIN_EXPORT)
			export_cmd(shell, cmd_args);
		if (builtin_num == BUILTIN_UNSET)
			unset_cmd(shell, shell->envs, cmd_args);
		if (builtin_num == BUILTIN_ECHO)
			echo_cmd(shell, cmd_args);
		if (builtin_num == BUILTIN_PWD)
			pwd_cmd(shell);
		if (builtin_num == BUILTIN_ENV)
			env_cmd(shell);
	}
	clean_array(cmd_args);
}

void	start_buitins_child(t_node	*cmd, t_shell	*shell, int builtin_num)
{
	char	**cmd_args;
	char	*cmd_str;

	cmd_str = (char *)cmd->value.cmd_val.args->val;
	if (cmd_str != NULL)
	{
		cmd_args = lst_to_char(&cmd->value.cmd_val.args);
		if (builtin_num == BUILTIN_CD)
		{
			cd_cmd(shell, cmd_args);
			exit(0);
		}
		if (builtin_num == BUILTIN_EXIT)
		{
			exit_cmd(shell, cmd_args);
		}
		if (builtin_num == BUILTIN_EXPORT)
		{
			export_cmd(shell, cmd_args);
			exit(0);
		}
		if (builtin_num == BUILTIN_UNSET)
		{
			unset_cmd(shell, shell->envs, cmd_args);
			exit(0);
		}
		if (builtin_num == BUILTIN_ECHO)
		{
			echo_cmd(shell, cmd_args);
			exit(0);
		}
		if (builtin_num == BUILTIN_PWD)
		{
			pwd_cmd(shell);
			exit(0);
		}
		if (builtin_num == BUILTIN_ENV)
		{
			env_cmd(shell);
			exit(0);
		}
	}
	clean_array(cmd_args);
}

int	check_builtins(t_node *cmd)
{
	char	*cmd_str;

	cmd_str = (char *)cmd->value.cmd_val.args->val;
	if (cmd_str != NULL)
	{
		if (!ft_strncmp(cmd_str, "cd", 2 ) || \
		!ft_strncmp(cmd_str, "CD", 2))
			return (BUILTIN_CD);
		if (!ft_strncmp(cmd_str, "exit", 4) || !ft_strncmp(cmd_str, "EXIT", 4))
			return (BUILTIN_EXIT);
		if (!ft_strncmp(cmd_str, "export", 6) || \
		!ft_strncmp(cmd_str, "EXPORT", 6))
			return (BUILTIN_EXPORT);
		if (!ft_strncmp(cmd_str, "unset", 5) || \
			!ft_strncmp(cmd_str, "UNSET", 5))
			return (BUILTIN_UNSET);
		if (!ft_strncmp(cmd_str, "echo", 5) || !ft_strncmp(cmd_str, "ECHO", 5))
			return (BUILTIN_ECHO);
		if (!ft_strncmp(cmd_str, "pwd", 5) || !ft_strncmp(cmd_str, "PWD", 5))
			return (BUILTIN_PWD);
		if (!ft_strncmp(cmd_str, "env", 5) || !ft_strncmp(cmd_str, "ENV", 5))
			return (BUILTIN_ENV);
	}
	return (BUILTIN_NONE);
}
