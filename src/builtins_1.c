#include "minishell.h"
#include "builtins.h"

void	env_cmd(t_shell	*shell)
{
	t_blist	*envs;

	envs = shell->envs;
	while (envs)
	{
		printf("%s=%s\n", (char *)envs->key, (char *)envs->val);
		envs = envs->next;
	}
	shell->exit_status = 0;
}

void	pwd_cmd(t_shell	*shell)
{
	char	pwd[PATH_MAX + 1];

	if (!getcwd(pwd, PATH_MAX + 1))
		printf("ERROR"); // сделать обработку
	ft_putendl_fd(pwd, 1);
	shell->exit_status = 0;
}

void    echo_cmd(t_shell    *shell, char **cmd_args)
{
    int i;
    int flag;

    flag = 0;
    i = 1;
    if (cmd_args && cmd_args[1] != NULL)
    {
        if (cmd_args[0] && cmd_args[1])
            flag = ft_strncmp(cmd_args[1], "-n", 3);
        if (!flag)
            i = 2;
        while (cmd_args[i])
		{
			ft_putstr_fd(cmd_args[i], 1);
			if (cmd_args[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
		if (flag)
			ft_putstr_fd("\n", 1);
		shell->exit_status = 0;
    }
    else if ((cmd_args && cmd_args[1] == NULL))
    {
        ft_putstr_fd("\n", 1);
    }
}
