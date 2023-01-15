#include "minishell.h"

t_blist	*create_envs_list(char	*envp)
{
	int		i;
	int		j;
	t_blist	*tmp;

	i = 0;
	tmp = malloc(sizeof(t_blist));
	if (!tmp)
		exit(1);
	while (envp[i] != '=')
		i++;
	tmp->key = ft_substr(envp, 0, i);
	if (!tmp->key)
		exit(1);
	j = i + 1;
	while (envp[j] != '\0' && envp[j] != '\n')
		j++;
	tmp->val = ft_substr(envp, i + 1, j - i);
	if (!tmp->val)
		exit(1);
	tmp->next = NULL;
	return (tmp);
}

void	parse_env_list(t_blist	**envs, char	*envp)
{
	t_blist	*tmp;

	if (!(*envs))
	{
		*envs = create_envs_list(envp);
	}
	else
	{
		tmp = *envs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_envs_list(envp);
	}
}

static void	free_one_env(t_blist *envs)
{
	free(envs->key);
	free(envs->val);
	free(envs);
}

void	remove_envs(t_blist **envs, char *key)
{
	t_blist	*save;
	t_blist	*tmp;

	if (!envs || !(*envs) || !key)
		return ;
	tmp = *envs;
	if (!(ft_strncmp(tmp->key, key, ft_strlen(key) + 1)))
	{
		save = tmp->next;
		free_one_env(tmp);
		*envs = save;
	}
	while (tmp && tmp->next)
	{
		if (!(ft_strncmp(tmp->next->key, key, ft_strlen(key) + 1)))
		{
			save = tmp->next->next;
			free_one_env(tmp->next);
			tmp->next = save;
		}
		tmp = tmp->next;
	}
}
