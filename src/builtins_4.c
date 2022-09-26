#include "builtins.h"
#include "clean.h"

void	error_message_unset(t_shell	*shell, char *str)
{
	print_shell(NULL, SHELL);
	ft_putstr_fd(": unset: \'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	shell->exit_status = 1;
}

void	check_arguments_unset(t_shell	*shell, char **args)
{
	int	i[2];

	i[0] = 1;
	while (args[i[0]])
	{
		i[1] = 0;
		while (args[i[0]][i[1]])
		{
			if (i[1] == 0 && args[i[0]][i[1]] >= '0' && args[i[0]][i[1]] <= '9')
			{
				error_message_unset(shell, args[i[0]]);
				break ;
			}
			if ((args[i[0]][i[1]] >= '!' && args[i[0]][i[1]] <= '/') || \
				(args[i[0]][i[1]] >= ':' && args[i[0]][i[1]] <= '@') || \
				(args[i[0]][i[1]] >= '[' && args[i[0]][i[1]] <= '^') || \
				(args[i[0]][i[1]] >= '{' && args[i[0]][i[1]] <= '~'))
			{
				error_message_unset(shell, args[i[0]]);
				break ;
			}
			i[1]++;
		}
		i[0]++;
	}
}

void	unset_cmd(t_shell	*shell, t_blist **envp, char **cmd_args)
{
	check_arguments_unset(shell, cmd_args);
	remove_envs(envp, cmd_args[1]);
	if (!ft_strncmp(cmd_args[1], "PATH", ft_strlen(cmd_args[1])))
	{
		clean_array(shell->env_arr);
	}
}
