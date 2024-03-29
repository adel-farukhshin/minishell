#ifndef SCANNER_H
# define SCANNER_H

# include "source.h"

typedef struct s_token {
	void			*key;
	void			*val;
	struct s_token	*next;
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

/**
 * @brief
 * Loops src. After every invocation curpos equals
 * the first character after the previous token.
 * 
 * @param src 
 * @return t_token* 
 * @return NULL: 1) EOF 2) error with quotes
 */
t_token	*find_token(t_src *src);

t_token	*create_token(char key, char *val);
void	free_token(t_token *tok, char m);
void	free_token_list(t_token *head);

/**
 * @brief 
 * Creates a val. Updates curpos, so it equals the last character of token. 
 * Returns token's value or null (in case of error).
 * 
 * @param src 
 * @param key 
 * @return char* 
 */
char	*create_val(t_src *src, char key);

char	find_key(char c);

long	redir_token(t_src *src, char *key);

/**
 * @brief 
 * Parses fields. Returns 0 on success and 1 on failure.
 * 
 * @param src 
 * @param key 
 * @param len 
 * @return char 
 */
char	process_fields(t_src *src, char key, long *len);

#endif