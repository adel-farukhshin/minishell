
#include <stdio.h>


#include "minishell.h"

#include "scanner.h"
#include "parser.h"

#include <stdlib.h>


int	main()
{
	t_src	src;
	t_token	*head;

	t_blist	*cmd;
	src.s = "cat > greeks";
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

	cmd = parse_tokens(head);
	// (void) cmd;
	// printf("%p\n", cmd);
	printf("%s\n", (char *)((t_list *)(cmd->val))->val);
	printf("%s\n", (char *)((t_list *)((t_command *)(cmd->key))->f_out)->val);

	free_token_list(head);

	// t_token	*tok = create_token(2, "greeks", 5);
	// printf("key %d, val %s\n", *(int *)tok->key, (char *)tok->val);
	// free_token(tok, 2);

}