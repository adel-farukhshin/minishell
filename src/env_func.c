#include "minishell.h"

 t_envs *create_envs_list(char   *envp)
{
    int i;
    int j;
    t_envs *tmp;

    i = 0;
    tmp = malloc(sizeof(t_envs));
    if (!tmp)
        printf("Malloc error");
    while(envp[i] != '=')
        i++;
    tmp->key = ft_substr(envp, 0, i);
    if (!tmp->key)
        printf("Error1");
    j = i + 1;
    while(envp[j] != '\0' && envp[j] != '\n')
        j++;
    tmp->value = ft_substr(envp, i + 1, j - i);
    if (!tmp->value)
        printf("Error");
    tmp->next = NULL;
    return (tmp);
}

void    parse_env_list(t_envs   **envs, char *envp)
{
     t_envs *tmp;
    
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

void    env_parsing(char   **envp,  t_envs  **envs)
{
    int i;

    i = -1;
    while(envp[++i])
        parse_env_list(envs, envp[i]);
}

void    env_to_arr(char **envp, t_shell *shell)
{
    int i;

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
