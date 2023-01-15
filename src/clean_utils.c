#include "clean.h"

void	clean_array(char	**arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	clean_envs_list(t_blist *list)
{	
	t_blist	*tmp_list;

	while (list)
	{
		tmp_list = list->next;
		free(list->key);
		list->key = NULL;
		free(list->val);
		list->val = NULL;
		free(list);
		list = tmp_list;
	}
}

void	clean_shell_data(t_shell *shell)
{
	if (shell->env_arr)
		clean_array(shell->env_arr);
	if (shell->envs)
		clean_envs_list(shell->envs);
	if (shell->export)
		clean_envs_list(shell->envs);
}
