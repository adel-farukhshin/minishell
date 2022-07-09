
#ifndef BLISTS_H
# define BLISTS_H

typedef struct s_blist {
	void			*key;
	void			*val;
	struct s_blist	*next;
}	t_blist;

t_blist	*blst_new(void *key, void *val);
void	blst_delone(t_blist *blst, void (*kdel)(void *),
			void (*vdel)(void *));
void	blst_clear(t_blist **blst, void (*kdel)(void *),
			void (*vdel)(void *));

void	blst_add_front(t_blist **blst, t_blist *new);
void	blst_add_back(t_blist **blst, t_blist *new);

#endif