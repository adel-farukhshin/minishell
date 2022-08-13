
#include <stdlib.h>
#include <stdio.h>

#include "minishell.h"
#include "blists.h"
#include "lists.h"

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

char	find_ext(char *s, long *len);

// @brief
// Takes s and checks, whether there is an environment variable. If there is a variable, returns 
// its value. Otherwise, returns null.
// @return 
static char	*env_var(char *s);
// static char *get_env_var(char *s);
// static void	update_counters(char *s, long *cur, long *start);

/**
 * @brief 
 * Joins all the values of list together. Return the joined string or null.
 * 
 * @param list 
 * @return char* 
 */
static char	*str_join(t_list *list);


char extend_arg(t_blist *tok)
{
	char	*s;
	char	*start;
	long	len;
	char	c;
	t_list	*list;

	s = (char *)tok->val;
	start = s;
	len = 0;
	list = NULL;
	
	// check extensions
	s = ft_strchr(s, '$');
	if (!s)
		return (0);

	while (s)
	{
		
		
		s = ft_strchr(s, '$');
		if (!s)
			break ;
		c = find_ext(s + 1, &len);
		if (c)
		{
			// add substring before extension
			*s = '\0';
			start = ft_strdup(start);
			if (!start)
			{
				lst_clear(&list, free);
				return (-1);
			}
			lst_add_back(&list, lst_new((void *)start));

			// add extension value
			if (c == 1) // pid
			{
				// atoi
				start = ft_strdup("4242");
			}
			else if (c == 2) // ecode
			{
				// atoi
				start = ft_strdup("77");
			}
			else // arg
			{
				// copy vname
				start = malloc(len);
				if (!start)
				{
					lst_clear(&list, free);
					return (-1);
				}
				ft_strncpy(start, s + 1, len - 1);
				// get value
				printf("var name: %s\n", start);
				start = env_var(start);
			}
			if (!start)
			{
				lst_clear(&list, free);
				return (-1);
			}
			lst_add_back(&list, lst_new((void *)start));
		}
		s += len;

		len = 0;
		start = s + len;
	}
	// join
	tok->val = str_join(list);
	lst_clear(&list, free);
	if (!tok->val)
		return (-1);

	return (0);
}

static char	*str_join(t_list *list)
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
	if (!val)
		return (NULL);
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

/*
char extend_arg(t_blist *tok)
{
	char	*s;
	long	cur;
	long	start;
	t_list	*words;
	char	*var;

	cur = 0;
	start = 0;
	s = tok->val;
	words = NULL;
	while (s[cur++])
	{
		if (s[cur] == '$') // replace with strchr
		{
			if (s[cur + 1] == '$' || s[cur + 1] == '?' || 
				(s[cur + 1] >= 'a' && s[cur + 1] <= 'z') ||
				(s[cur + 1] >= 'A' && s[cur + 1] <= 'Z') ||
				s[cur + 1] == '_')
			{
				s[cur] = '\0';
				lst_add_back(&words, lst_new((void *)ft_strdup(s + start)));
				if (s[cur + 1] == '$') // PID
					// ft_atoi
					lst_add_back(&words, lst_new((void *)ft_strdup("4242")));
				else if (s[cur + 1] == '?') // ECODE
					// ft_atoi
					lst_add_back(&words, lst_new((void *)ft_strdup("777")));
				else
				{
					var = env_var(s + cur + 1);
					if (var)
						lst_add_back(&words, lst_new(var));
				}
				update_counters(s + cur + 1, &cur, &start);
				// update start and cur
			}
				
		}
	}
	printf("extension: %s\n", (char *)words->val);

	// be careful in joining: strdup can return null

	// null the tok->val
	return (0);
}
*/

char	find_ext(char *s,  long *len)
{
	long	i;

	*len = 1;
	i = 0;
	if (s[i] == '$' || s[i] == '?')
	{
		*len += 1;
		if (s[i] == '$') // PID
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


	// *len = i;
	// while (s && s[i++])
	// {
	// 	s = ft_strchr(s, '$');
	// 	if (s[i] == '$') // replace with strchr
	// 	{
	// 		if (s[i + 1] == '$' || s[i + 1] == '?' || 
	// 			(s[i + 1] >= 'a' && s[i + 1] <= 'z') ||
	// 			(s[i + 1] >= 'A' && s[i + 1] <= 'Z') ||
	// 			s[i + 1] == '_')
	// 		{
	// 			*st += i;
	// 			if (s[i + 1] == '$' || s[i + 1] == '?')
	// 				*end += i + 1; 
	// 		}
	// 	}
	// }
// }


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

// static char *get_env_var(char *s)
// {
// 	long	i;
// 	char	c;
// 	char	*val;

// 	i = 0;
// 	while (s[i++])
// 	{
// 		c = s[i];
// 		if ((c >= 'a' && c <= 'z') || 
// 			(c >= 'A' && c <= 'Z') ||
// 			(c == '_'))
// 			continue ;
// 		else if (i && c >= '0' && c <= '9')
// 			continue ;		
// 		else
// 			break ;
// 	}
// 	// printf("%d\n", i);
// 	val = malloc(i + 1);
// 	if (!val)
// 		return (val);
// 	ft_strncpy(val, s, i);
// 	return (val);
// }

// static void	update_counters(char *s, long *cur, long *start)
// {
// 	long	i;
// 	char	c;

// 	i = 0;
// 	if (*s == '$' || *s == '?')
// 		*cur += 1;
// 	else
// 		while (s[i++])
// 		{
// 			c = s[i];
// 			if ((c >= 'a' && c <= 'z') || 
// 				(c >= 'A' && c <= 'Z') ||
// 				(c == '_'))
// 				continue ;
// 			else if (i && c >= '0' && c <= '9')
// 				continue ;		
// 			else
// 				break ;
// 		}
// 	*cur += i;
// 	*start = *cur;
// }
