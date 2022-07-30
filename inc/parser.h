#ifndef PARSER_H
# define PARSER_H

#include "scanner.h"
#include "node.h"

/**
 * @brief 
 * Takes the list of tokens. Analyzes them in accordance with grammar rules. 
 * Returns the cmd_node, pipe_node or error_node.
 * 
 * @param t 
 * @return t_node* 
 */
t_node *parse(t_token *t);


#endif