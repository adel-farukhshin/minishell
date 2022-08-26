
#ifndef LISTS_H
# define LISTS_H

typedef struct s_list {
	void			*val;
	struct s_list	*next;
}	t_list;

t_list	*lst_new(void *val);
void	lst_delone(t_list *lst, void (*del)(void *));
void	lst_clear(t_list **lst, void (*del)(void *));

void	lst_add_back(t_list **lst, t_list *n);
void	lst_add_front(t_list **lst, t_list *n);

int		lst_size(t_list *lst);

/**
 * @brief Creates array of char pointers. Traverses all nodes in lst and copies
 * pointers to array. On success returns the char pointer to the start of array. 
 * On failure returns the null. Deallocates all the nodes. Nulls the lst. 
 * 
 * @param lst 
 * @return char** 
 */
char	**lst_to_char(t_list **lst);

#endif