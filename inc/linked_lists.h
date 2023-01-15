#ifndef LINKED_LISTS_H
# define LINKED_LISTS_H

# include <stdbool.h>
# include "blists.h"

typedef struct s_l_list {
	t_blist	*head;
	t_blist	*next;
}	t_l_list;

/**
 * @brief 
 * A linked_list constructor. Head must not be null. 
 * Creates linked_list, next points to the head.
 * Returns linked_list or null (if unsuccessful)
 * 
 * @param head 
 * @param next 
 * @return t_l_list* 
 * @return null
 */
t_l_list	*ll_new(t_blist *head);

/**
 * @brief 
 * Checks the next node.
 * 
 * @param list 
 * @return true 
 * @return false 
 */
bool		ll_has_next(t_l_list *list);

/**
 * @brief 
 * Returns the next node. Does not update the next node. 
 * 
 * @param list 
 * @return t_blist* 
 */
t_blist		*ll_peek(t_l_list *list);

/**
 * @brief 
 * Returns the next node. Updates the next node.
 * 
 * @param list 
 * @return t_blist* 
 */
t_blist		*ll_take(t_l_list *list);

/**
 * @brief 
 * Changes the value of the node. Frees old value. 
 * New_val must be pre-allocated and must not be null.
 * 
 * @param node 
 */
void		ll_change_value(t_blist *node, void *new_val);

/**
 * @brief 
 * Frees all allocated memory. Returns null to null the pointer
 * 
 * @param list 
 * @return void* 
 */
void		*ll_drop(t_l_list *list);

#endif