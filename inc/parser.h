
#ifndef PARSER_H
# define PARSER_H

# include "scanner.h"
# include "lists.h"
# include "blists.h"

typedef struct s_command {
	char				pipe;
	int					nb;
	t_list				*f_in;
	t_list				*f_out;
	t_list				*f_ap;
	t_list				*delim;
}	t_command;

# define M_ARG 1

t_blist	*parse_tokens(t_token *tok);

#endif