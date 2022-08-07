
#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>

#include "parser.h"

long	count_exts(char *s);
char	what_ext(char *s, long *len);
t_src	*create_ext_arr(t_token *t, long nb);
void	free_ext_arr(t_src *arr, long nb);
long	total_len(t_token *t, t_src *e_arr);


char	word_extend(t_token *tok)
{
	long	nb_exts;
	t_src	*ext_arr;
	// char	*d;

	nb_exts = count_exts((char *)tok->val);
	printf("in word_extend: %s\n", (char *)tok->val);
	// printf("%s nb_exts %ld\n", (char *)tok->val, nb_exts);
	if (!nb_exts)
		return (0);
	ext_arr = create_ext_arr(tok, nb_exts);
	if (!ext_arr)
		return (1);
	// d = malloc(total_len(t, ext_arr) + 1);

	return (0);
}

long	count_exts(char *s)
{
	long	nb;
	long	i;
	long	l;
	
	i = 0;
	nb = 0;
	while (s[i++])
	{
		l = 0;
		if (what_ext(s + i, &l))
			nb++;
		i += l;
	}
	return (nb);
}

static char	is_v_valid(char c, long i);

char	what_ext(char *s, long *len)
{
	long	l;

	if (!s || !len)
		return (-1);
	l = 0;
	if (s[l] == '$')
	{
		if (s[++l] == '$' || s[l] == '?')
		{
			*len = l;
			if (s[l] == '$')
				return (PID);
			return (ECODE);
		}
		else if (is_v_valid(s[l], l - 1))
		{
			while (is_v_valid(s[l], l - 1))
				l++;
			*len = l - 1;
			return (VAR);
		}
	}
	return (0);
}

static char	is_v_valid(char c, long i)
{
	
	if ((c >= 'a' && c <= 'z') || 
		(c >= 'A' && c <= 'Z') ||
		(c == '_'))
			return (1);
	else if (i && c >= '0' && c <= '9')
		return (1);
	return (0);
}

#include "minishell.h"
static void	save_ext(char *s, t_src *arr, char mode);

t_src	*create_ext_arr(t_token *t, long nb)
{
	t_src	*arr;
	long	i;
	char	mode;
	long	l;

	i = 0;
	arr = malloc (sizeof(t_src) * nb); // it is not NULL terminated!
	if (!arr)
		return (NULL);
	nb = 0;
	while (((char *)t->val)[i])
	{
		
		l = 0;
		printf("%s; i %ld; l %ld\n", ((char *)t->val) + i, i, l);
		mode = what_ext(((char *)t->val) + i, &l);
		if (mode)
			save_ext((char *)t->val + i, arr + nb, mode);
		if (mode && !(arr + nb)->s)
		{
			free_ext_arr(arr, nb);
			return (NULL);
		}
		(arr + nb)->curpos = i;
		nb++;
		i += l;
		i++;
		printf("%s; i %ld; l %ld\n", ((char *)t->val) + i, i, l);
	}
	return (arr);
}

void	free_ext_arr(t_src *arr, long nb)
{
	while (--nb >= 0)
		free(arr[nb].s);
	free(arr);
}

static char	*get_var(char *s, long len);


//error here
static void	save_ext(char *s, t_src *arr, char mode) // можно избавиться от mode или сократить его название
{
	long	l;

	arr->len = 2;
	if (mode == ECODE)
		arr->s = ft_itoa(0);
	else if (mode == PID)
		arr->s = ft_itoa(2121);
	else if (mode == VAR)
	{
		l = 1;
		while (is_v_valid(s[l], l - 1))
			l++;
		arr->s = get_var(s + 1, --l - 1);
		printf("arr.s: %s\n", arr->s);
		if (!arr->s)
			return ;
		arr->len = l;
	}
}

static char *get_var(char *s, long len)
{
	char	*vname;
	char	*ret;

	vname = malloc(len + 1);
	if (!vname)
		return (NULL);
	ft_strncpy(vname, s, len);
	printf("vname: %s\n", vname);
	ret = getenv(vname);
	free(vname);
	return (ret);
}

// long	total_len(t_token *t, t_src *e_arr)
// {
// 	long	ret;
// 	long	i;
	
// 	ret = 0;
// 	ret += ft_strlen((char *)t->val);
// 	while ((e_arr + i)->s)
// 	{
// 		printf("cur e_arr: %s\n", (e_arr + i)->s);
// 		ret -= (e_arr + i)->len;
// 		ret += ft_strlen((e_arr + i)->s);
// 		i++;
// 	}
// 	return (ret);
// }
