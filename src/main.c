
#include <stdio.h>


#include "minishell.h"

#include "scanner.h"

#include <stdlib.h>


int	main()
{

	t_src	src;
	t_token	*head;
	t_token	*tok;

	src.s = " greeks \'field\' \"\" \"exp_field\" | > < >> << ";
	src.curpos = 0;
	src.len = ft_strlen(src.s);
	
	head = tokenize(&src);
	if (!head)
		printf("error\n");
	tok = head;
	while (tok)
	{
		printf("key %d, val %s\n", *(int *)tok->key, (char *)tok->val);
		tok = tok->next;
	}
	free_token_list(head);

	// t_token	*tok = create_token(2, "greeks", 5);
	// printf("key %d, val %s\n", *(int *)tok->key, (char *)tok->val);
	// free_token(tok, 2);

}