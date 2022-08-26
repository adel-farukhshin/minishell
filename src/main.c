
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

	// Create src
	// src.s = " ";
	// src.s = "ls";
	// src.s = "ls file";
	src.s = "ls | wc -l";
	// src.s = "cat > h1 | cat -l";
	// src.s = "cat > h1 >> h2 >h3 | cat -l";
	// src.s = "\"a$?\" \"$$\"";
	// src.s = "ec\"h\"o";
	// src.s = " greeks \'field\' \"f \" \" a\" \" \"exp_field\" | > < >> << ";
	src.curpos = 0;
	src.len = ft_strlen(src.s);
	printf("%s\n", src.s);
	
	// Create tokens' list
	head = tokenize(&src);
	if (!head)
		printf("error\n");
	// turn tokens' list to t_l_list structure
	t_l_list	*list = ll_new((t_blist *)head);
	printf("the head: _%s_\n", (char *)list->head->val);

	t_node *cmd;
	cmd = parse(list);
	print_node(cmd, 0);
	ll_drop(list);

	// Execution
	// if (cmd->type == error_node)
	// 	printf("error: %s\n", cmd->value.error_msg);
	// else if (cmd->type == cmd_node)
	// 	printf("cmd: %s\n", (char *)cmd->value.cmd_val.args->val);
	// else
	// 	printf("pipe:\ncmd _%s_\ncmd2 _%s_\n", (char *)cmd->value.pipe_val.left->value.cmd_val.args->val,
	// 		(char *)cmd->value.pipe_val.right->value.cmd_val.args->val);

	// Free cmd
	node_drop(cmd);
}