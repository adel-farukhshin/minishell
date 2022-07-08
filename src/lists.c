
#include <stdlib.h>
#include <unistd.h>
#include "lists.h"

t_list	*lst_new(void *val)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->val = val;
	node->next = NULL;
	return (node);
}

void	lst_delone(t_list *lst)
{
	if (lst)
	{
		free(lst->val);
		free(lst);
	}	
}

void	lst_clear(t_list **lst)
{
	t_list	*tmp;

	if (!lst || !*lst)
		return ;
	while (lst && *lst)
	{
		tmp = (*lst)->next;
		lst_delone(*lst);
		*lst = tmp;
	}
}
