
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

void	lst_delone(t_list *lst, void (*del)(void *))
{
	if (!del)
		return ;
	if (lst)
	{
		(*del)(lst->val);
		free(lst);
	}	
}

void	lst_clear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!del || !lst || !*lst)
		return ;
	while (lst && *lst)
	{
		tmp = (*lst)->next;
		lst_delone(*lst, del);
		*lst = tmp;
	}
}

void	lst_add_back(t_list **lst, t_list *n)
{
	while (*lst)
		lst = &((*lst)->next);
	*lst = n;
}

void	lst_add_front(t_list **lst, t_list *n)
{
	if (!*lst)
		n->next = NULL;
	else
		n->next = *lst;
	*lst = n;
}

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
// #include <stdio.h>
// #include "minishell.h"

// int	main(void)
// {
// 	t_list	*start = NULL;
// 	t_list	*new;
// 	char	*templ = ft_strdup("a");
// 	char	*s;
// 	char	mode = 0;

// 	for (int i = 0; i < 3; i++)
// 	{
// 		new = lst_new(ft_strdup(templ));
// 		printf("new %s\n", new->val);
// 		if (mode)
// 			lst_add_front(&start, new);
// 		else
// 			lst_add_back(&start, new);
// 		templ[0]++;
// 	}
// 	printf("start %s\n", start->val);
// 	lst_clear(&start, &free);
// 	free(templ);
// }
