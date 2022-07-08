
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

void	blst_delone(t_blist *blst)
{
	if (blst)
	{
		free(blst->key);
		free(blst->val);
		free(blst);
	}	
}

void	blst_clear(t_blist **blst)
{
	t_blist	*tmp;

	if (!blst || !*blst)
		return ;
	while (blst && *blst)
	{
		tmp = (*blst)->next;
		blst_delone(*blst);
		*blst = tmp;
	}
}
