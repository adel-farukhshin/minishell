#include "builtins.h"

void	ft_search_oldpwd(char **oldpwd, t_blist *envs)
{
	t_blist	*tmp;
	char	tmp1[1024];

	tmp = envs;
	while (tmp)
	{
		if (!ft_strncmp("PWD", tmp->key, 4))
			break ;
		tmp = tmp->next;
	}
	if (tmp != NULL)
		*oldpwd = ft_strdup(tmp->val);
	else if (tmp == NULL)
	{
		getcwd(tmp1, 1024);
		*oldpwd = ft_strdup(tmp1);
	}
	if (*oldpwd == NULL)
		perror_exit("", 12);
}

void	ft_cd_error(t_shell *shell, char **arr, int flag, char *oldpwd)
{
	free(oldpwd);
	if (flag == 1)
	{
		print_shell(NULL, SHELL);
		ft_putstr_fd(": cd: HOME not set \n", 2);
	}
	else if (flag == 2)
	{
		print_shell(NULL, SHELL);
		ft_putstr_fd(": cd: ", 2);
		ft_putstr_fd(arr[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	shell->exit_status = 1;
}
