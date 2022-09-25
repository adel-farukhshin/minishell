#include "builtins.h"

void	error_message_unset(t_shell	*shell, char *str)
{
	// ft_print_shell(NULL, SHELL);
	ft_putstr_fd(": unset: \'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	shell->exit_status = 1;
}

void	check_arguments_unset(t_shell	*shell, char **cmd_args)
{
	int	i[2];

	i[0] = 1;
	while (cmd_args[i[0]])
	{
		i[1] = 0;
		while (cmd_args[i[0]][i[1]])
		{
			if (i[1] == 0 && cmd_args[i[0]][i[1]] >= '0' && cmd_args[i[0]][i[1]] <= '9')
			{
				error_message_unset(shell, cmd_args[i[0]]);
				break ;
			}
			if ((cmd_args[i[0]][i[1]] >= '!' && cmd_args[i[0]][i[1]] <= '/') || \
				(cmd_args[i[0]][i[1]] >= ':' && cmd_args[i[0]][i[1]] <= '@') || \
				(cmd_args[i[0]][i[1]] >= '[' && cmd_args[i[0]][i[1]] <= '^') || \
				(cmd_args[i[0]][i[1]] >= '{' && cmd_args[i[0]][i[1]] <= '~'))
			{
				error_message_unset(shell, cmd_args[i[0]]);
				break ;
			}
			i[1]++;
		}
		i[0]++;
	}
}

void	delete_argument(t_blist *del, t_blist *envp, int num)
{
	t_blist	*tmp;

	tmp = envp;
	num--;
	while (num != 0)
	{
		tmp = tmp->next;
		num--;
	}
	tmp->next = tmp->next->next;
	if (del)
	{
		free(del->key);
		free(del->val);
		free(del);
	}
}

void	find_argument(t_blist *envp, char **cmd_args)
{
	t_blist	*tmp;
	int		len;
	int		i;
	int		num;

	i = 1;
	while (cmd_args[i])
	{
		num = 0;
		tmp = envp;
		len = ft_strlen(cmd_args[i]);
		while (tmp)
		{
			if (!ft_strncmp(cmd_args[i], tmp->key, len))
			{
				delete_argument(tmp, envp, num);
				break ;
			}
			tmp = tmp->next;
			num++;
		}
		i++;
	}
}

void	unset_cmd(t_shell    *shell, t_blist *envp, char **cmd_args)
{
	check_arguments_unset(shell, cmd_args);
	find_argument(envp, cmd_args);
}
