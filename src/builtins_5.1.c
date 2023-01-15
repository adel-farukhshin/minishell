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
