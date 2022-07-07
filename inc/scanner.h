
#ifndef SCANNER_H
# define SCANNER_H

# include "source.h"

typedef struct s_token {
	void	*key;
	void	*val;
	void	*next;
}	t_token;

# define SEP 1 // is_space
# define WORD 2 // all other
# define FIELD 3 // ''
# define EXT_FIELD 4 // ""
# define PIPE 5 // |
# define REDIR_OUT 6 // >
# define REDIR_IN 7 // <
# define REDIR_APPEND 8 // >>
# define REDIR_INSOURCE 9 // <<

t_token	*tokenize(t_src *src);

t_token	*find_token(t_src *src);
t_token	*create_token(char key, char *val, long l);
void	free_token(t_token *tok, char m);
void	free_token_list(t_token *head);



#endif