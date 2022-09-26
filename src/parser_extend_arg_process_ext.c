#include <stdlib.h>
#include <stdio.h>

#include "minishell.h"
#include "blists.h"
#include "lists.h"
#include "parser.h"

char		add_substring(char *s, char *start, t_list **list);
t_list		*create_ext(char c, char *s, long len,
				t_shell *sh);
static char	*env_var(char *s);

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

char	add_substring(char *s, char *start, t_list **list)
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
