#ifndef PARSER_H
# define PARSER_H

#include "scanner.h"
#include "node.h"
#include "linked_lists.h"
#include "minishell.h"

/**
 * @brief 
 * Takes the list of tokens. Analyzes them in accordance with grammar rules. 
 * Returns the cmd_node, pipe_node or error_node.
 * 
 * @param t 
 * @return t_node* 
 */
t_node *parse(t_l_list *token_list, t_shell *sh);

/**
 * @brief 
 * Joins all the values of list together. Return the joined string or null. Does not
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
char extend_arg(t_blist *tok, t_shell *sh);


#endif