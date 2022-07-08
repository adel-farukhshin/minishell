
#ifndef BLISTS_H
# define BLISTS_H

typedef struct s_blist {
	void			*key;
	void			*val;
	struct s_blist	*next;
}	t_blist;

t_blist	*blst_new(void *key, void *val);
void	blst_delone(t_blist *blst);
void	blst_clear(t_blist **blst);

#endif