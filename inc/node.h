#ifndef NODE_H
# define NODE_H

# include "lists.h"

typedef enum e_node_type {
	error_node = -1,
	cmd_node = 0,
	pipe_node = 1
} t_node_type;

typedef struct s_node t_node;

typedef const char *t_error_value;

typedef struct s_cmd_value {
	t_list	*args;
} t_cmd_value;

typedef struct s_pipe_value {
	t_node	*left;
	t_node	*right;
} t_pipe_value;

typedef union u_node_value {
	t_cmd_value		cmd_val;
	t_pipe_value	pipe_val;
	t_error_value	error_msg;
} t_node_value;

struct s_node {
	t_node_type		type;
	t_node_value	value;
};

/**
 * @brief 
 * Creates a cmd_node and adds cmd_name to list of arguments (args). Cmd_name must not be null and
 * must be pre-allocated. Returns created node or null in case of memory error
 * @param s 
 * @return t_node* 
 */
t_node *cmd_node_new(const char *cmd_name);

/**
 * @brief 
 * Adds arg to the list of args. Arg must not be null and must be pre-allocated.
 * Returns 0, if it was sucessful, and -1 if not. 
 * 
 * @param cmd_name 
 * @return char 
 */
char	cmd_add_arg(t_node *cmd, const char *arg);

/**
 * @brief 
 * Creates and initializes pipe_node. Returns node or null in case of memory error
 * 
 * @param left 
 * @param right 
 * @return t_node* 
 */
t_node *pipe_node_new(t_node *left, t_node *right);

/**
 * @brief
 * Creates an initializes error_node. Returns node or null in case of memory error
 * 
 * @param msg 
 * @return t_node* 
 */
t_node *error_node_new(const char *msg);

/**
 * @brief 
 * Frees all allocated memory. Returns null to null the pointer
 * 
 * @param node 
 * @return void* 
 */
void *node_drop(t_node *node);

void print_node(t_node *node, int intend);

#endif