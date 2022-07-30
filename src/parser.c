#include <stdio.h>

#include <stdlib.h>

#include "parser.h"

// #include "blists.h"
// #include "scanner.h"
// #include "minishell.h"

// NODE		::= CMD | PIPE
// CMD		::= SEP* + ARG + ARG* + [[R_OUT]* + [R_IN]* + [R_APPEND]* + [R_INSOURCE]*]* + [PIPE + CMD]*
// ARG		::= WORD | FIELD | EXT_FIELD
// PIPE		::= CMD + CMD

static t_node	*parse_cmd(t_token *t);

t_node *parse(t_token *t)
{
	t_node	*node;

	node = parse_cmd(t);
	return (node);
}

static t_node	*parse_cmd(t_token *t)
{
	char	*arg;

	
}




