
#ifndef T_LIST_H
# define T_LIST_H

typedef struct s_list {
	void			*val;
	struct s_list	*next;
}	t_list;

typedef struct s_blist {
	void			*key;
	void			*val;
	struct s_blist	*next;
}	t_blist;



#endif