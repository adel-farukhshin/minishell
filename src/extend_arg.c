#include <stdlib.h>
#include <stdio.h>

#include "minishell.h"
#include "blists.h"
#include "lists.h"
#include "parser.h"

/**
 * @brief 
 * Checks, whether there is an extension. Len must be null.
 * If extension is found, updates len variable. 
 * Adding len to s will lead to the first character after extension. 
 * Returns 1, 2 and 3 if the extension is '$$', "$?" or '$arg' respectively.
 * Otherwise, returns 0.
 * 
 * @param s 
 * @param len  
 * @return char 
 */

char		find_ext(char *s, long *len);

static char	*env_var(char *s);

char 		loop_exts(char *s, char *start,
				t_list **list, t_shell *sh);

char		process_ext(char *s, char *start,
				t_list **list, t_shell *sh);

char extend_arg(t_blist *tok, t_shell *sh)
{
	char	*s;
	char	*start;
	t_list	*list;

	s = (char *)tok->val;
	start = s;
	list = NULL;
	s = ft_strchr(s, '$');
	if (!s)
		return (0);
	if (loop_exts(s, start, &list, sh) == -1)
		return (-1);
	tok->val = str_join(list);
	lst_clear(&list, free);
	if (!tok->val)
		return (-1);
	return (0);
}

char loop_exts(char *s, char *start,
			t_list **list, t_shell *sh)
{
	long	len;

	len = 0;
	while (s)
	{
		s = ft_strchr(s, '$');
		if (!s)
			break ;
		len = process_ext(s, start, list, sh);
		if (len == -1)
		{
			lst_clear(list, free);
			return (-1);
		}
		s += len;
		start = s;
	}
	return (0);
}

char	add_substring(char *s, char *start, t_list **list);
t_list	*create_ext(char c, char *s, long len,
			t_shell *sh);

char	process_ext(char *s, char *start,
			t_list **list, t_shell *sh)
{
	char	c;
	long	len;
	t_list	*l;

	len = 0;
	c = find_ext(s + 1, &len);
	if (c)
	{
		if (add_substring(s, start, list) == -1)
			return (-1); 
		l = create_ext(c, s, len, sh);
		if (!l)
			return (-1);
		lst_add_back(list, l);
	}
	return (len);
}

char add_substring(char *s, char *start, t_list **list)
{
	*s = '\0';
	start = ft_strdup(start);
	if (!start)
	{
		lst_clear(list, free);
		return (-1);
	}
	lst_add_back(list, lst_new((void *)start));
	return (0);
}

t_list	*create_ext(char c, char *s, long len,
			t_shell *sh)
{
	char	*start;

	if (c == 1)
		start = ft_itoa(sh->pid);
	else if (c == 2)
		start = ft_itoa(sh->exit_status);
	else
	{
		start = malloc(len);
		if (!start)
			return (NULL);
		ft_strncpy(start, s + 1, len - 1);
		start = env_var(start);
	}
	if (!start)
		return (NULL);
	return (lst_new((void *)start));
}


char	*str_join(t_list *list)
{
	long	len;
	t_list	*tmp;
	char	*val;
	char	*cur;

	if (!list)
		return (NULL);
	tmp = list;
	len = 0;
	while (list->next)
	{
		len += ft_strlen((char *)list->val);
		list = list->next;
	}
	val = malloc(len + 1);
	cur = val;
	while (tmp)
	{
		len = ft_strlen((char *)tmp->val);
		ft_strncpy(cur, (char *)tmp->val, len);
		cur += len;
		tmp = tmp->next;
	}	
	*cur = '\0';
	return (val);
}

char	find_ext(char *s,  long *len)
{
	long	i;

	*len = 1;
	i = 0;
	if (s[i] == '$' || s[i] == '?')
	{
		*len += 1;
		if (s[i] == '$')
			return (1);
		return (2);
	}
	while (*s)
	{
		if ((*s >= 'a' && *s <= 'z') ||
			(*s >= 'A' && *s <= 'Z') ||	*s == '_')
			*len += 1;
		else if (*len > 2 && *s >= '0' && *s <= '9')
			*len += 1;
		else
			break ;
		s++;
	}
	if (*len > 1)
		return (3);
	return (0);
}

static char	*env_var(char *s)
{
	char	*val;
	char	*ret;

	if (!s)
		return (NULL);
	ret = NULL;
	val = getenv(s);
	if (val)
		ret = ft_strdup(val);
	free(s);
	return (ret);
}
