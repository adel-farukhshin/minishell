#include "builtins.h"

void	ft_print_sort(t_shell *shell)
{
	sort_export(&shell->export);
	print_export(shell->export);
}

void	copy_env_to_export(t_shell *shell, t_blist *envs)
{
	t_blist	*tmp;
	t_blist	*new;
	char	*key1;
	char	*value1;

	tmp = envs;
	while (tmp)
	{
		key1 = ft_strdup(tmp->key);
		value1 = ft_strdup(tmp->val);
		if (key1 == NULL || value1 == NULL)
			perror_exit("", 12);
		new = blst_new(key1, value1);
		if (new == NULL)
			perror_exit("", 12);
		blst_add_back(&shell->export, new);
		tmp = tmp->next;
	}
}

int	ft_error_message_export(t_shell *shell, char *str)
{
	print_shell(NULL, SHELL);
	ft_putstr_fd(": export: \'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	shell->exit_status = 1;
	return (-1);
}

int	ft_check_arguments_export(t_shell *shell, char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	while (str[i])
	{
		if (i == 0 && str[i] >= '0' && str[i] <= '9')
			return (ft_error_message_export(shell, str));
		if ((str[i] >= '!' && str[i] <= '-') || \
				(str[i] >= ';' && str[i] <= '<') || \
					(str[i] >= '>' && str[i] <= '@') || \
						(str[i] >= '[' && str[i] <= '^') || \
						(str[i] >= '{' && str[i] <= '~'))
			return (ft_error_message_export(shell, str));
		if (str[i] == '=')
			res = 2;
		i++;
	}
	return (res);
}

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = malloc(n + 1);
	if (NULL == ptr)
		return (NULL);
	else
	{
		while (i < n)
		{
			ptr[i] = s[i];
			++i;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}
