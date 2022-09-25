#include "builtins.h"

void	printing_elem(t_blist *tmp)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(tmp->key, 1);
	if (tmp->val != NULL)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(tmp->val, 1);
		ft_putstr_fd("\"\n", 1);
	}
	else if (tmp->val == NULL)
		ft_putstr_fd("\n", 1);
}

void	front_back_split(t_blist *head, t_blist **tmp1, t_blist **tmp2)
{
	t_blist	*fast;
	t_blist	*slow;

	slow = head;
	fast = head->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*tmp1 = head;
	*tmp2 = slow->next;
	slow->next = NULL;
}

t_blist	*sorted_export(t_blist *tmp1, t_blist *tmp2)
{
	t_blist	*result;

	result = NULL;
	if (tmp1 == NULL)
		return (tmp2);
	if (tmp2 == NULL)
		return (tmp1);
	if (ft_strncmp(tmp1->key, tmp2->key, ft_strlen(tmp1->key)) < 0)
	{
		result = tmp1;
		result->next = sorted_export(tmp1->next, tmp2);
	}
	else
	{
		result = tmp2;
		result->next = sorted_export(tmp1, tmp2->next);
	}
	return (result);
}

void	sort_export(t_blist **export)
{
	t_blist	*head;
	t_blist	*tmp1;
	t_blist	*tmp2;

	head = *export;
	if ((head == NULL) || (head->next == NULL))
		return ;
	front_back_split(head, &tmp1, &tmp2);
	sort_export(&tmp1);
	sort_export(&tmp2);
	*export = sorted_export(tmp1, tmp2);
}

void	print_export(t_blist *export)
{
	t_blist	*tmp;

	tmp = export;
	while (tmp)
	{
		printing_elem(tmp);
		tmp = tmp->next;
	}
}

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
			printf("ERROR");
			// ft_perror_exit_child("", 12);
		new = blst_new(key1, value1);
		if (new == NULL)
			printf("ERROR");
			// ft_perror_exit_child("", 12);
		blst_add_back(&shell->export, new);
		tmp = tmp->next;
	}
}

int	ft_error_message_export(t_shell *shell, char *str)
{
	// ft_print_shell(NULL, SHELL);
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

int	ft_change_value(t_blist *llist, char *key, char *value)
{
	t_blist	*tmp;
	int		len;

	tmp = llist;
	len = ft_strlen(key);
	while (tmp)
	{
		if (ft_strncmp(key, tmp->key, (len + 1)) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return (0);
	else if (ft_strncmp(key, tmp->key, (len + 1)) == 0)
	{
		free(tmp->val);
		tmp->val = value;
		free(key);
	}
	return (1);
}

void	ft_newelem_export(t_shell *shell, char *str)
{
	int		i;
	char	*key;
	char	*value;
	t_blist	*new;

	i = 0;
	while (str[i] && str[i] != '=')
		++i;
	key = ft_strndup(str, i);
	if (str[i] == '=')
		++i;
	value = ft_strdup(str + i);
	if (key == NULL || value == NULL)
		printf("ERROR");
	if (ft_change_value(shell->export, key, value))
		return ;
	new = blst_new(key, value);
	if (new == NULL)
		printf("ERROR");
	blst_add_back(&shell->export, new);
}

void	ft_newelem_env(t_shell *shell, char *str)
{
	int		i;
	char	*key;
	char	*value;
	t_blist	*new;

	i = 0;
	while (str[i] && str[i] != '=')
		++i;
	key = ft_strndup(str, i);
	if (str[i] == '=')
		++i;
	value = ft_strdup(str + i);
	if (key == NULL || value == NULL)
		printf("ERROR");
	if (ft_change_value(shell->envs, key, value))
		return ;
	new = blst_new(key, value);
	if (new == NULL)
		printf("ERROR");
	blst_add_back(&shell->envs, new);
}

void	ft_adding_to_struct(t_shell *shell, char **cmd_args)
{
	int	i;
	int	put;

	i = 1;
	while (cmd_args[i])
	{
		put = ft_check_arguments_export(shell, cmd_args[i]);
		if (put > 0)
		{
			ft_newelem_export(shell, cmd_args[i]);
			if (put == 2)
				ft_newelem_env(shell, cmd_args[i]);
		}
		i++;
	}
}

void	export_cmd(t_shell *shell, char **cmd_args)
{
	if (shell->export == NULL)
		copy_env_to_export(shell, shell->envs);
	if (cmd_args[0] != NULL && cmd_args[1] == NULL)
		ft_print_sort(shell);
	else if (cmd_args[0] != NULL && cmd_args[1] != NULL)
		ft_adding_to_struct(shell, cmd_args);
}
