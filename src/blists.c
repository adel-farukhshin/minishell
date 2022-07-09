
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
