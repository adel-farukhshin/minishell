
#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include "node.h"

t_node *cmd_node_new(const char *cmd_name)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (node);
	node->type = cmd_node;
	node->value.cmd_val.args = lst_new((void *)cmd_name);
	if (!node->value.cmd_val.args)
	{
		free(node);
		return (NULL);
	}
	node->value.cmd_val.r_out = NULL;
	node->value.cmd_val.r_in = NULL;
	node->value.cmd_val.r_app = NULL;
	node->value.cmd_val.r_ins = NULL;
	return (node);
}

char	cmd_add_arg(t_node *cmd, const char *arg)
{
	t_list	*new;

	new = lst_new((void *)arg);
	if (!new)
		return (-1);
	lst_add_back(&cmd->value.cmd_val.args, new);
	return (0);
}

char	cmd_add_redir(t_node *cmd, const char *redir, char type)
{
	t_list	*new_file;

	new_file = lst_new((void*)redir);
	if (!new_file)
		return (-1);
	if (type == R_OUT)
		lst_add_back(&cmd->value.cmd_val.r_out, new_file);
	else if (type == R_IN)
		lst_add_back(&cmd->value.cmd_val.r_in, new_file);
	else if (type == R_APP)
		lst_add_back(&cmd->value.cmd_val.r_app, new_file);
	else if (type == R_INS)
		lst_add_back(&cmd->value.cmd_val.r_ins, new_file);
	return (0);
}

t_node *pipe_node_new(t_node *left, t_node *right)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (node);
	node->type = pipe_node;
	node->value.pipe_val.left = left;
	node->value.pipe_val.right = right;
	return (node);
}

t_node *error_node_new(const char *msg)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (node);
	node->type = error_node;
	node->value.error_msg = msg;
	return (node);	
}

void *node_drop(t_node *node)
{
	if (node->type == pipe_node)
	{
		node_drop(node->value.pipe_val.left);
		node_drop(node->value.pipe_val.right);
	}
	else if (node->type == cmd_node)
	{
		lst_clear(&(node->value.cmd_val.args), free);
		lst_clear(&(node->value.cmd_val.r_in), free);
		lst_clear(&(node->value.cmd_val.r_out), free);
		lst_clear(&(node->value.cmd_val.r_app), free);
		lst_clear(&(node->value.cmd_val.r_ins), free);
	}
	free(node);
	return (NULL);
}

void	print_intends(int intend);
void	print_redirs(t_node *node, int intend);
void	print_redir(const char *msg, t_list *f, int intend);

void print_node(t_node *node, int intend)
{
	t_list *arg;

	if (node->type == error_node)
		printf("Error: %s\n", node->value.error_msg);
	else if (node->type == cmd_node)
	{
		print_intends(intend);
		arg = node->value.cmd_val.args;
		if (arg && arg->val)
			printf("%s\n", (char *)arg->val);
		else
			printf("cmd is null");
		print_intends(intend + 2);
		while (arg && arg->val)
		{
			printf("%s ", (char *)arg->val);
			arg = arg->next;
		}
		printf("\n");
		print_redirs(node, intend + 2);
	}
	else
	{
		printf("Pipe\n");
		print_node(node->value.pipe_val.left, intend + 2);
		print_node(node->value.pipe_val.right, intend + 2);
	}
}

void	print_intends(int intend)
{
	while (intend > 0)
	{
		printf(" ");
		intend--;
	}
}

void	print_redirs(t_node *node, int intend)
{
	t_list *r;

	r = node->value.cmd_val.r_in;
	if (r)
		print_redir("r_in", r, intend);
	r = node->value.cmd_val.r_out;
	if (r)
		print_redir("r_out", r, intend);
	r = node->value.cmd_val.r_app;
	if (r)
		print_redir("r_app", r, intend);
	r = node->value.cmd_val.r_ins;
	if (r)
		print_redir("r_ins", r, intend);
}

void	print_redir(const char *msg, t_list *f, int intend)
{
	print_intends(intend);
	printf("%s:", msg);
	while (f)
	{
		printf(" %s", (char *)f->val);
		f = f->next;
	}
	printf("\n");
}


// int	main()
// {
	// t_node *left;
	// t_node *right;
	// int 	i;

	// char	*s = malloc(4);	
	// for (i = 0; i < 3; i++)
	// 	s[i] = 'a';
	// s[i] = '\0';
	
	// char	*s1 = malloc(4);
	// for (i = 0; i < 3; i++)
	// 	s1[i] = 'b';
	// s[i] = '\0';
	
	// left = cmd_node_new(s);
	// printf("%s\n", (char *)left->value.cmd_val.args->val);

	// right = cmd_node_new(s1);
	// printf("%s\n", (char *)right->value.cmd_val.args->val);

	// t_node *p = pipe_node_new(left, right);
	// printf("in pipe %s and %s\n", (char *)p->value.pipe_val.left->value.cmd_val.args->val,
	// 	(char *)p->value.pipe_val.right->value.cmd_val.args->val);

	// p = node_drop(p);

	// char	*s3 = "error";
	// t_node *e = error_node_new(s3);
	// printf("the end: %s\n", e->value.error_msg);

	// e = node_drop(e);

// /*
// 	t_node	*node;
// 	char	*str; 
// 	int		i;

// 	str = malloc(4);	
// 	for (i = 0; i < 3; i++)
// 		str[i] = 'a';
// 	str[i] = '\0';
// 	node = cmd_node_new(str);

// 	str = malloc(4);	
// 	for (i = 0; i < 3; i++)
// 		str[i] = 'b';
// 	str[i] = '\0';

// 	cmd_add_arg(node, str);
// 	printf("%s\n", (char *) node->value.cmd_val.args->next->val);

// 	node_drop(node);
// */
// }