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
        printf("ERROR!"); // TODO
}

void	ft_print_shell(char *str, char *shell)
{
	if (str != NULL)
		ft_putstr_fd(str, 2);
	write(2, shell, ft_strlen(shell));
	write(2, "\b\b", 2);
}

void	ft_cd_error(t_shell *shell, char **arr, int flag, char *oldpwd)
{
	free(oldpwd);
	if (flag == 1)
	{
		// ft_print_shell(NULL, SHELL);
		ft_putstr_fd(": cd: HOME not set \n", 2);
	}
	else if (flag == 2)
	{
		// ft_print_shell(NULL, SHELL);
		ft_putstr_fd(": cd: ", 2);
		ft_putstr_fd(arr[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	shell->exit_status = 1;
}

int	ft_without_argument(t_blist *envs, char *path)
{
	t_blist	*tmp;

	tmp = envs;
	while (tmp)
	{
		if (ft_strncmp("HOME", tmp->key, 5) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp != NULL && ft_strncmp("HOME", tmp->key, 5) == 0)
	{
		path = tmp->val;
		chdir(path);
	}
	else
		return (1);
	return (0);
}

void	ft_cd_pwd(t_blist *tmp, int flag, t_blist *envs)
{
	char	*key;
	char	*value;
	char	tmp1[1024];
	t_blist	*new;

	getcwd(tmp1, 1024);
	if (flag == 1)
	{
		free(tmp->val);
		tmp->val = ft_strdup(tmp1);
		if (tmp->val == NULL)
			printf("ERROR!"); // TODO
	}
	else if (flag == 2)
	{
		key = ft_strdup("PWD");
		value = ft_strdup(tmp1);
		if (key == NULL || value == NULL)
			printf("ERROR!"); // TODO
		new = blst_new(key, value);
		if (!new)
			printf("ERROR!"); // TODO
		blst_add_back(&envs, new); // checking
	}
}

void	ft_cd_oldpwd(t_blist *tmp, int flag, t_blist *envs, char *oldpwd)
{
	char	*key;
	char	*value;
	t_blist	*new;

	if (flag == 1)
	{
		free(tmp->val);
		tmp->val = oldpwd;
	}
	else if (flag == 2)
	{
		key = ft_strdup("OLDPWD");
		value = ft_strdup(oldpwd);
		free(oldpwd);
		if (key == NULL || value == NULL)
			printf("ERROR!"); // TODO
		new = blst_new(key, value);
		if (!new)
			printf("ERROR!"); // TODO
		blst_add_back(&envs, new); // checking
	}
}

void	ft_added_pwd_oldpwd(char *oldpwd, t_blist *envs)
{
	int		pwd_f;
	int		oldpwd_f;
	t_blist	*tmp;

	tmp = envs;
	pwd_f = 1;
	oldpwd_f = 1;
	while (tmp)
	{
		if (!ft_strncmp("PWD", tmp->key, 4))
		{
			ft_cd_pwd(tmp, 1, NULL);
			pwd_f = 0;
		}
		else if (!ft_strncmp("OLDPWD", tmp->key, 7))
		{
			ft_cd_oldpwd(tmp, 1, NULL, oldpwd);
			oldpwd_f = 0;
		}
		tmp = tmp->next;
	}
	if (pwd_f == 1)
		ft_cd_pwd(NULL, 2, envs);
	if (oldpwd_f == 1)
		ft_cd_oldpwd(NULL, 2, envs, oldpwd);
}

void	cd_cmd(t_shell   *shell, char **cmd_args)
{
	int		mistake;
	char	*oldpwd;
	char	*path;

	oldpwd = NULL;
	path = NULL;
	mistake = 0;
	ft_search_oldpwd(&oldpwd, shell->envs);
	if (cmd_args[1] == NULL)
	{
		mistake = ft_without_argument(shell->envs, path);
		if (mistake == 1)
			ft_cd_error(shell, cmd_args, 1, oldpwd);
	}
	else
	{
		mistake = chdir(cmd_args[1]);
		if (mistake == -1)
			ft_cd_error(shell, cmd_args, 2, oldpwd);
	}
	if (mistake == 0)
		ft_added_pwd_oldpwd(oldpwd, shell->envs);
}