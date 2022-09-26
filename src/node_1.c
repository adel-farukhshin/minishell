#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include "node.h"

t_node	*error_node_new(const char *msg)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (node);
	node->type = error_node;
	node->value.error_msg = msg;
	return (node);
}

void	*node_drop(t_node *node)
{
	if (node->type == pipe_node)
	{
		node_drop(node->value.pipe_val.left);
		node_drop(node->value.pipe_val.right);
	}
	else if (node->type == cmd_node)
	{
		lst_clear(&(node->value.cmd_val.args), free);
		blst_clear(&(node->value.cmd_val.redirs), free, free);
	}
	free(node);
	return (NULL);
}

// void	print_intends(int intend);
// void	print_redirs(t_node *node, int intend);

// void	print_node(t_node *node, int intend)
// {
// 	t_list	*arg;

// 	if (node->type == error_node)
// 		printf("Error: %s\n", node->value.error_msg);
// 	else if (node->type == cmd_node)
// 	{
// 		print_intends(intend);
// 		arg = node->value.cmd_val.args;
// 		if (arg && arg->val)
// 			printf("%s\n", (char *)arg->val);
// 		else
// 			printf("cmd is null");
// 		print_intends(intend + 2);
// 		while (arg && arg->val)
// 		{
// 			printf("%s ", (char *)arg->val);
// 			arg = arg->next;
// 		}
// 		printf("\n");
// 		print_redirs(node, intend + 2);
// 	}
// 	else
// 	{
// 		print_intends(intend);
// 		printf("Pipe\n");
// 		print_node(node->value.pipe_val.left, intend + 2);
// 		print_node(node->value.pipe_val.right, intend + 2);
// 	}
// }

// void	print_intends(int intend)
// {
// 	while (intend > 0)
// 	{
// 		printf(" ");
// 		intend--;
// 	}
// }

// void	print_redirs(t_node *node, int intend)
// {
// 	t_blist *r;

// 	r = node->value.cmd_val.redirs;
// 	if (!r)
// 		return ;
// 	print_intends(intend);
// 	printf("redirs:");
// 	while (r)
// 	{
// 		printf(" %d-%s", *(char *)r->key, (char *)r->val);
// 		r = r->next;
// 	}
// 	printf("\n");
// }
