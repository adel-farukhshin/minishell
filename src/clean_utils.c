#include "clean.h"

void	clean_array(char	**arr)
{
	int	i;

	i = 0;
	while (arr[i])
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

	tmp_list = list;
	while (list)
	{
		free(tmp_list->key);
		tmp_list->key = NULL;
		free(tmp_list->val);
		tmp_list = tmp_list->next;
		tmp_list->val = NULL;
		free(tmp_list);
		list = NULL;
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
