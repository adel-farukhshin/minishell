#ifndef PARSER_H
# define PARSER_H

#include "scanner.h"
#include "node.h"
#include "linked_lists.h"

/**
 * @brief 
 * Takes the list of tokens. Analyzes them in accordance with grammar rules. 
 * Returns the cmd_node, pipe_node or error_node.
 * 
 * @param t 
 * @return t_node* 
 */
t_node *parse(t_l_list *token_list);

/**
 * @brief 
 * Private function.
 * 
 * @return 0 - extension isn't needed; 1 - successful extension; -1 - error
 */
char extend_arg(t_blist *tok);


#endif