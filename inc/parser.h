
#ifndef PARSER_H
# define PARSER_H

# include "lists.h"

typedef struct s_command {
	char				pipe;
	int					nb;
	t_list				*f_in;
	t_list				*f_out;
	t_list				*f_ap;
	t_list				*delim;
}	t_command;

#endif