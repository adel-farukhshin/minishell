#include <stdlib.h>
#include <unistd.h>
#include "lists.h"

int	lst_size(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	**lst_to_char(t_list **lst)
{
	int		size;
	char	**ret_string;
	t_list	*cur_node;
	t_list	*tmp;
	int		cur;

	if (*lst == NULL)
		return (NULL);
	size = lst_size(*lst);
	ret_string = malloc(sizeof(char *) * (size + 1));
	if (!ret_string)
		return (NULL);
	ret_string[size] = NULL;
	cur_node = *lst;
	cur = 0;
	while (cur_node)
	{
		ret_string[cur] = (char *)cur_node->val;
		tmp = cur_node;
		cur++;
		cur_node = tmp->next;
		free(tmp);
	}
	*lst = NULL;
	return (ret_string);
}
