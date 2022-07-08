
#ifndef LISTS_H
# define LISTS_H

typedef struct s_list {
	void			*val;
	struct s_list	*next;
}	t_list;

t_list	*lst_new(void *val);
void	lst_delone(t_list *lst);
void	lst_clear(t_list **lst);

#endif