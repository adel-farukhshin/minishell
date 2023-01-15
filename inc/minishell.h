#ifndef MINISHELL_H
# define MINISHELL_H

# include "node.h"
# include "minishell.h"
# include "../libft/libft.h"
# include "../inc/blists.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h> 
# include <unistd.h>

typedef struct s_context
{
	int	fd[2];
	int	fd_close;
}	t_context;

typedef struct s_shell
{
	int		exit_status;
	int		pid;
	t_blist	*envs;
	t_blist	*export;
	char	**env_arr;
}	t_shell;

void	ft_strncpy(char *dst, const char *src, long len);
int		ft_isspace(char c);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
void	env_to_list_func(char	**envp, t_shell shell);
void	env_parsing(char	**envp, t_blist	**envs);
void	env_to_arr(char **envp, t_shell *shell);
t_blist	*create_envs_list(char	*envp);
void	parse_env_list(t_blist	**envs, char	*envp);
void	remove_envs(t_blist **envs, char *key);
#endif