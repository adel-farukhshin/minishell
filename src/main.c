
#include <stdio.h>


#include "minishell.h"

#include "scanner.h"
#include "parser.h"
#include "blists.h"
#include "linked_lists.h"

#include <stdlib.h>


int	main()
{
	t_src	src;
	t_token	*head;

	// src.s = "cat test.c > greeks";
	// src.s = "cat test.c greeks | greeks";
	src.s = "\"a$?\" \"$$\"";
	// src.s = "\"ads\"";

	// src.s = " greeks \'field\' \"f \" \" a\" \" \"exp_field\" | > < >> << ";
	printf("%s\n", src.s);
	src.curpos = 0;
	src.len = ft_strlen(src.s);
	
	head = tokenize(&src);
	if (!head)
		printf("error\n");
	// t_token	*tok;
	// tok = head;
	// while (tok)
	// {
	// 	printf("key %d, val %s\n", *(int *)tok->key, (char *)tok->val);
	// 	tok = tok->next;
	// }

	t_l_list	*list = ll_new((t_blist *)head);

	printf("the head: _%s_\n", (char *)list->head->val);

	t_node *cmd;
	cmd = parse(list);
	printf("after parse\n");

	if (cmd->type == error_node)
		printf("error: %s\n", cmd->value.error_msg);
	else if (cmd->type == cmd_node)
		printf("cmd: %s\n", (char *)cmd->value.cmd_val.args->val);
	else
		printf("pipe:\ncmd _%s_\ncmd2 _%s_\n", (char *)cmd->value.pipe_val.left->value.cmd_val.args->val,
			(char *)cmd->value.pipe_val.right->value.cmd_val.args->val);

	printf("cmd arg: %s\n", (char *)cmd->value.cmd_val.args->next->val);

	if (ll_has_next(list))
		printf("cur token: %d\n", *(char *)ll_peek(list)->key);
/*
	t_blist	*cmd;
	cmd = parse_tokens(list);
	// (void) cmd;
	// printf("%p\n", cmd);
	printf("%s\n", (char *)((t_list *)(cmd->val))->val);
	printf("%s\n", (char *)((t_list *)((t_command *)(cmd->key))->f_out)->val);

	free_token_list(head);
*/

	// t_token	*tok = create_token(2, "greeks", 5);
	// printf("key %d, val %s\n", *(int *)tok->key, (char *)tok->val);
	// free_token(tok, 2);

}