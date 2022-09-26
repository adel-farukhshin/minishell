
#include <stdlib.h>
#include <unistd.h>
#include "linked_lists.h"

t_l_list	*ll_new(t_blist *head)
{
	t_l_list	*new;

	new = malloc(sizeof(t_l_list));
	if (!new)
		return (NULL);
	new->head = head;
	new->next = head;
	return (new);
}

bool	ll_has_next(t_l_list *list)
{
	if (!list->next)
		return (false);
	else
		return (true);
}

t_blist	*ll_peek(t_l_list *list)
{
	return (list->next);
}

t_blist	*ll_take(t_l_list *list)
{
	t_blist	*tmp;

	tmp = list->next;
	list->next = list->next->next;
	return (tmp);
}

/*
#include <string.h>
#include <stdio.h>

int	main()
{
	t_blist	*a;

	a = blst_new(strdup("a"), strdup("a"));
	blst_add_back(&a, blst_new(strdup("b"), strdup("b")));
	printf("%s\n", (char *)a->val);
	printf("%s\n", (char *)a->next->val);

	t_l_list	*list;

	list = ll_new(a);
	printf("list: _%s_  _%s_\n", (char *)list->head->val, (char *)list->next->val);

	printf("list: %d\n", ll_has_next(list));

	a = ll_peek(list);
	printf("peek: %s\n", (char *)a->val);

	a = ll_take(list);
	printf("take: %s\n", (char *)a->val);
	printf("take: next is _%s_\n", (char *)list->next->val);

	ll_change_value(list->next, strdup("c"));
	a = ll_peek(list);
	printf("change value: %s\n", (char *)a->val);

	list = ll_drop(list);
}
*/