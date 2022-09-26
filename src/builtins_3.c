#include "builtins.h"

int	ft_is_number(char *str)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			res = 1;
		i++;
	}
	return (res);
}

void	exit_cmd(t_shell *shell, char **cmd_args)
{
	int		i;
	char	c;

	if (cmd_args[1] == NULL)
		exit(shell->exit_status);
	else if (cmd_args[2] != NULL && !ft_is_number(cmd_args[1]))
	{
		print_shell("exit\n", SHELL);
		ft_putstr_fd(": exit: too many arguments\n", 2);
	}
	else if (ft_is_number(cmd_args[1]))
	{
		print_shell("exit\n", SHELL);
		ft_putstr_fd(": exit: ", 2);
		ft_putstr_fd(cmd_args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	else
	{
		i = ft_atoi(cmd_args[1]);
		c = i;
		ft_putstr_fd("exit\n", 1);
		exit(c);
	}
}
