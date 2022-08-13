
#include <stdlib.h>
#include <unistd.h>
#include "blists.h"

t_blist	*blst_new(void *key, void *val)
{
	t_blist	*node;

	node = malloc(sizeof(t_blist));
	if (!node)
		return (NULL);
	node->key = key;
	node->val = val;
	node->next = NULL;
	return (node);
}

void	blst_delone(t_blist *blst, void (*kdel)(void *),
			void (*vdel)(void *))
{
	if (!kdel || !vdel)
		return ;
	if (blst)
	{
		(*kdel)(blst->key);
		(*vdel)(blst->val);
		free(blst);
	}	
}

void	blst_clear(t_blist **blst, void (*kdel)(void *),
			void (*vdel)(void *))
{
	t_blist	*tmp;

	if (!blst || !*blst || !kdel || !vdel)
		return ;
	while (blst && *blst)
	{
		tmp = (*blst)->next;
		blst_delone(*blst, kdel, vdel);
		*blst = tmp;
	}
}

void	blst_add_back(t_blist **blst, t_blist *n)
{
	while (*blst)
		blst = &((*blst)->next);
	*blst = n;
}

void	blst_add_front(t_blist **blst, t_blist *n)
{
	if (!*blst)
		n->next = NULL;
	else
		n->next = *blst;
	*blst = n;
}

// #include <stdio.h>
// #include "minishell.h"

// int	main(void)
// {
// 	t_blist	*start = NULL;
// 	t_blist	*new;
// 	char	*templ = ft_strdup("a");
// 	char	*s;
// 	char	mode = 1;

// 	for (int i = 0; i < 3; i++)
// 	{
// 		new = blst_new(ft_strdup(templ), ft_strdup(templ));
// 		printf("new: key %s val %s\n", new->key, new->val);
// 		if (mode)
// 			blst_add_front(&start, new);
// 		else
// 			blst_add_back(&start, new);
// 		templ[0]++;
// 	}
// 	printf("start: key %s val %s\n", start->key, start->val);
// 	blst_clear(&start, &free, &free);
// 	free(templ);
// }
