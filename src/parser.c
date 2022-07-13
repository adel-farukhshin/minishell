#include <stdio.h>

#include <stdlib.h>

#include "blists.h"
#include "parser.h"
#include "scanner.h"
#include "minishell.h"


/*
blist.key = t_command;
blist.value = args;
blist.next = next;
*/

t_blist	*command_create(void *key, void *val);
void	t_command_delete(void *cmd);

t_token	*check_pipe_syntax(t_token *tok, char *mode);
t_token	*check_redir_syntax(t_token *tok, char *mode);

char	*word_create(t_token **token);
void	append(t_blist *cmd, t_list *new, char *mode);

/* // Prototypes 
// t_token	*handle_token(t_token *tok, t_blist *word_lims,
// 				 t_blist *cmd);
// t_token	*word_update(t_blist *word_lims, t_token *tok);
// char	*word_create(t_blist *word_lims);
*/

t_blist	*parse_tokens(t_token *tok)
{
	t_blist	*cmds;
	t_blist	*cur_cmd;
	char	*word;
	char	mode;

	cmds = command_create(NULL, NULL); // free
	if (!cmds)
		return (NULL);
	cur_cmd = cmds;
	mode = 0;
	// printf("parse: before while\n");
	while (tok)
	{
		if (*(int *)tok->key == SEP)
		{
			tok = tok->next;
			continue ;
		}
		else if (*(int *)tok->key == PIPE)
		{
			tok = check_pipe_syntax(tok->next, &mode);
			if (!tok)
				return (NULL);
			((t_command *)(cur_cmd->key))->pipe = 1;
			cur_cmd = command_create(NULL, NULL);
			blst_add_back(&cmds, cur_cmd);
		}
		else if (*(int *)tok->key >= REDIR_OUT && *(int *)tok->key <= REDIR_INSOURCE)
		{
			tok = check_redir_syntax(tok, &mode);
			if (!tok)
				return (NULL);
		}
		else if (*(int *)tok->key >= WORD && *(int *)tok->key <= EXT_FIELD)
			mode = M_ARG;
		else
			return (NULL);
		word = word_create(&tok);		
		if (!word)
		{
			// printf("word is null\n");
			tok = NULL;
			return (NULL);
		}
		append(cur_cmd, lst_new(word), &mode);
		// printf("after append %p\n", ((t_list *)((t_command *)cur_cmd->key)->f_out));
		// printf("parse: in while, before tok increase %s\n", (char *)tok->val);
		tok = tok->next;
		
	}
	// if (!tok)
	// {
	// 	// parse_free();
	// 	return (NULL);
	// }
	return (cmds);
}

/* // Parse_tokens Variation
t_blist	*parse_tokens(t_token *tok)
{
	t_blist	*cmd;
	t_blist	word_lims;

	cmd = command_create(NULL, NULL); // free
	if (!cmd)
		return (NULL);
	word_lims.key = NULL;
	while (tok)
	{
		tok = handle_token(tok, &word_lims, cmd);
		if (!tok)
		{
			// free cmd
			blst_clear(&cmd, &t_command_delete, &lst_delone); // add free
			return (NULL);
		}
		tok = tok->next;
	}
	return (cmd);
}
*/

t_blist	*command_create(void *key, void *val)
{
	t_blist *cmd;
	
	if (!key)
	{
		key = malloc(sizeof(t_command));
		if (!key)
			return (NULL);
	}
	cmd = blst_new(key, val);
	if (!cmd)
		return (NULL);
	return (cmd);
}

void	t_command_delete(void *a)
{
	t_command	*cmd;

	cmd = (t_command *)a;
	lst_clear(&(cmd->f_in), &free);
	lst_clear(&(cmd->f_out), &free);
	lst_clear(&(cmd->f_ap), &free);
	lst_clear(&(cmd->delim), &free);
	free(cmd);
}

t_token	*check_pipe_syntax(t_token *tok, char *mode)
{
	char	key;

	if (!tok)
		return (NULL);
	key = *(char *)tok->key;
	*mode = 0;
	if (key >= WORD && key <= EXT_FIELD)
		*mode = M_ARG;
	else if (key == SEP)
	{
		tok = tok->next;
		if (!tok)
			return (NULL);
		key = *(char *)tok->key;
		if (key >= WORD && key <= EXT_FIELD)
			*mode = M_ARG;
		else if (key >= REDIR_OUT && key <= REDIR_INSOURCE)
		{
			tok = check_redir_syntax(tok, mode);
		}
		else
			return (NULL);
	}
	return (tok);
}

t_token	*check_redir_syntax(t_token *tok, char *mode)
{
	char	key;

	if (!tok)
		return (NULL);
	*mode = *(char *)tok->key;
	tok = tok->next;
	if (!tok)
		return (NULL);
	key = *(char *)tok->key;
	if (key >= WORD && key <= EXT_FIELD)
		return (tok);
	else if (key == SEP)
	{
		tok = tok->next;
		if (!tok)
			return (NULL);
		key = *(char *)tok->key;
		if (key >= WORD && key <= EXT_FIELD)
			return (tok);
	}
	*mode = 0;
	return (NULL);
}

static void	data_cpy(char *s, t_token *start, t_token *end);

char	*word_create(t_token **token)
{
	char	*ret;
	t_token	*tmp;
	t_token	*end;
	long	len;

	// printf("word_create: before while \n");
	len = 0;
	tmp = *token;
	end = tmp;
	while(tmp && *(int *)tmp->key >= WORD &&
			*(int *)tmp->key <= EXT_FIELD)
	{
		// printf("word_create: in while %s\n", (char *)tmp->val);
		end = tmp;
		len += ft_strlen((char *)end->val);
		tmp = tmp->next;
		// printf("word_create: in while: after tmp next\n");
	}
	// printf("word_create: before while \n");
	ret = malloc(sizeof(char) * len + 1);
	// printf("word_create: ret is %s; len %lu\n", ret, len);
	if (!ret)
		return (NULL); // можно и токен обнулять
	data_cpy(ret, *token, tmp);
	*token = end;
	return (ret);
}


static void	data_cpy(char *s, t_token *start, t_token *end)
{
	long	i;
	long	j;

	i = 0;
	while (start != end)
	{
		j = 0;
		while (((char *)start->val)[j])
			s[i++] = ((char *)start->val)[j++];
		start = start->next;
	}
	s[i] = '\0';
}


void	append(t_blist *cmd, t_list *new, char *mode)
{
	if (*mode == M_ARG)
		lst_add_back((t_list **)&cmd->val, new);
	else if (*mode == REDIR_OUT)
		lst_add_back((t_list **)&((t_command *)cmd->key)->f_out, new);
	else if (*mode == REDIR_IN)
		lst_add_back((t_list **)&((t_command *)cmd->key)->f_in, new);
	else if (*mode == REDIR_APPEND)
		lst_add_back((t_list **)&((t_command *)cmd->key)->f_ap, new);
	else if (*mode == REDIR_INSOURCE)
		lst_add_back((t_list **)&((t_command *)cmd->key)->delim, new);	
	*mode = 0; // по итогу нужно обнулять
}


// t_token	*handle_token(t_token *tok, t_blist *word_lims,
// 				t_blist *cmd)
// {
// 	if (tok->key >= WORD && tok->key <= EXT_FIELD)
// 		word_update(&word_lims, tok);
// 	else
// 	{
// 		if (word_lims->key) // можно это условие в функцию перенести
// 			lst_add_back(&(cmd->val), word_create(word_lims));
// 		if (tok->key == PIPE)
// 			tok = handle_pipe(cmd, tok);
// 		else if (tok->key >= REDIR_OUT &&
// 				tok->key <= REDIR_INSOURCE)
// 			tok = handle_redir(cmd, tok);
// 		if (!tok)
// 			return (NULL);
// 	}
// 	return (tok);
// }


/* // Word extension
static t_token	*word_extension(t_token *tok);

t_token		*word_update(t_blist *word_lims, t_token *tok)
{
	// extension
	if (tok->key == WORD || tok->key == EXT_FIELD)
		tok = word_extension(tok);
	if (!tok);
		return (NULL);

	// update word_lims
	if (!word_lims->key)
		word_lims->key = tok;
	else
		word_lims->val = tok;
	return (tok);
}

t_src	*src_create(char *s, long curpos);
void	src_delete(void *src);

int	create_ext_list(t_src *src, t_list *ext_lst);

#include "minishell.h"
# define QMARK 1
# define DOL 2
# define VAR 3
t_token	*ext_create(int exit_code, int pid, long curpos, long *len, char mode);
long	total_len(t_src *src, t_list *ext_lst);
char	is_ext_var(char *s);

static t_token	*word_extension(t_token *tok)
{
	t_src	*src;
	t_list	*ext_lst;

	src = src_create(ft_strdup((char *)tok->val), 0);
	if (create_ext_list(&src, &ext_lst))
	{
		src_delete(src); // s was duped
		return (NULL);
	}
	free(tok->val);
	tok->val = malloc(total_len(src, ext_lst)); // here can be an error; so if we free this, it would be seg
	if (!tok->val)
	// error handling
	data_cpy();
	lst_clear(&ext_lst, &free);
	src_delete(src); // because s was strduped 
	return (tok);
}

int	create_ext_list(t_src *src, t_list *ext_lst)
{

		while (src->s[src->curpos++])
	{
		if (src->s[src->curpos] == '$')
		{
			if (src->s[src->curpos + 1] == '?')
				// last exit_code
				tok = ext_create(0, 4412, i, &len, QMARK);
			else if (src->s[src->curpos + 1] == '$')
				// pid
				tok = ext_create(0, 4412, i, &len, DOL);
			else if (is_ext_var(s[i + i]))
				tok = ext_create(0, 4412, i, &len, VAR);
			else
				continue ;
			if (!tok->val)
				return (NULL);
		}
	}
	lst_clear(&ext_lst, &src_delete);


	return (0);
}

t_token	*ext_create(int exit_code, int pid, long curpos, long *len, char mode)
{
	t_token
	long	len;

	len = 0;
	if (mode == QMARK)
	{
		// len exit_code
		len = 2;

	}
	else if (mode = DOL)

	else


}

long	total_len(t_src *src, t_list *ext_lst)
{
	// + 1 for \0
}

t_src	*src_create(char *s, long curpos)
{
	t_src	*src;

	if (!s)
		return (NULL);
	src = malloc(sizeof(t_src));
	if (!src)
		return (NULL);
	src->s = s;
	src->curpos = curpos;
	src->len = ft_strlen(src->s);
}

void	src_delete(void *a)
{
	t_src	*src;

	src = (t_src *)a;
	free(src->s); // if s is duped; but if is not, it is not required
	free(src);
}

int	count_extensions(char *s)
{
	int	count;
	int	i;
	
	count = 0;
	i = 0;
	while (s[i++])
	{
		if (s[i] == '$')	
		{
			if (s[i + 1] == '?' || s[i + 1] == '$' ||
				s[i + 1] == is_ext_valid(s[i + 1]))
				count++;
		}
	}
	return (count);
}

char	is_ext_var(char *s)
{
	while () // !is_space || !EOF

}
*/

// char	*word_create(t_blist *word_lims)
// {


// 	word_lims->key = NULL;
// 	word_lims->val = NULL;
// }

// handle_pipe()
// {
// 	// check_syntax

// 	// change flag
// 	// create_cmd

// }