#ifndef PARSER_H
# define PARSER_H

# include "scanner.h"
# include "node.h"
# include "linked_lists.h"
# include "minishell.h"

/**
 * @brief 
 * Takes the list of tokens. Analyzes them in accordance with grammar rules. 
 * Returns the cmd_node, pipe_node or error_node.
 * 
 * @param t 
 * @return t_node* 
 */
t_node	*parse(t_l_list *token_list, t_shell *sh);

// parser_parse_arg.c
char	parse_arg(t_l_list *t, char **ret_val, t_shell *sh);
char	add_args(t_l_list *t, t_node *cmd, t_shell *sh);

char	process_ext(char *s, char *start,
			t_list **list, t_shell *sh);
char	find_ext(char *s, long *len);

/**
 * @brief 
 * Joins all the values of list together. 
 * Return the joined string or null. Does not
 * free list.
 * 
 * @param list 
 * @return char* 
 */
char	*str_join(t_list *list);

/**
 * @brief 
 * Private function.
 * 
 * @return 0 - extension isn't needed; 1 - successful extension; -1 - error
 */
char	extend_arg(t_blist *tok, t_shell *sh);

#endif