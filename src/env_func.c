#include "minishell.h"

char	*search_envs(t_blist **envs, char *key)
{
	t_blist	*tmp;

	if (!envs || !(*envs) || !key)
		return (0);
	tmp = *envs;
	while (tmp)
	{
		if ((ft_strncmp(tmp->key, key, ft_strlen(tmp->key) + 1)) == 0)
			return (tmp->val);
		tmp = tmp->next;
	}
	return (0);
}

void	env_parsing(char	**envp, t_blist	**envs)
{
	int		i;
	char	*number;
	char	*temp;
	char	*temp2;

	i = -1;
	while (envp[++i])
		parse_env_list(envs, envp[i]);
	if (search_envs(envs, "SHLVL"))
	{
		number = ft_strdup(search_envs(envs, "SHLVL"));
		remove_envs(envs, "SHLVL");
		temp2 = ft_itoa(ft_atoi(number) + 1);
		temp = ft_strjoin("SHLVL=", temp2);
		parse_env_list(envs, temp);
		free(temp2);
		free(temp);
		free(number);
	}
	else
	{
		parse_env_list(envs, "SHLVL=1");
	}
}

void	env_to_arr(char **envp, t_shell *shell)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
		i++;
	shell->env_arr = malloc(sizeof(char *) * (i + 1));
	if (!shell->env_arr)
		return ;
	i = 0;
	while (envp[i])
	{
		shell->env_arr[i] = ft_strdup(envp[i]);
		if (!shell->env_arr[i])
			return ;
		i++;
	}
	shell->env_arr[i] = NULL;
}
