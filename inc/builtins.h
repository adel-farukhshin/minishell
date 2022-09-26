#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include <sys/syslimits.h>
# include <unistd.h>
# include <stdio.h>
# include "executor.h"

typedef enum e_builtin_nb
{
	BUILTIN_CD,
	BUILTIN_ECHO,
	BUILTIN_ENV,
	BUILTIN_EXPORT,
	BUILTIN_EXIT,
	BUILTIN_PWD,
	BUILTIN_UNSET,
	BUILTIN_NONE
}	t_builtin_nb;

int		check_builtins(t_node *cmd);
void	start_buitins_parent(t_node	*cmd, t_shell	*shell, int builtin_num);
void	start_buitins_child(t_node	*cmd, t_shell	*shell, int builtin_num);
void	exe_one_builtin(t_node *cmd, t_context	*ctx, \
	t_shell	*shell, int builtin_num);
void	cd_cmd(t_shell	*shell, char **cmd_args);
void	env_cmd(t_shell	*shell);
void	pwd_cmd(t_shell	*shell);
void	echo_cmd(t_shell	*shell, char	**cmd_args);
void	exit_cmd(t_shell *shell, char **cmd_args);
void	unset_cmd(t_shell	*shell, t_blist	**envp, char **cmd_args);
void	export_cmd(t_shell *shell, char **cmd_args);
void	ft_print_shell(char *str, char *shell);
void	remove_envs(t_blist **envs, char *key);
void	ft_cd_error(t_shell *shell, char **arr, int flag, char *oldpwd);
void	ft_search_oldpwd(char **oldpwd, t_blist *envs);
void	printing_elem(t_blist *tmp);
void	front_back_split(t_blist *head, t_blist **tmp1, t_blist **tmp2);
t_blist	*sorted_export(t_blist *tmp1, t_blist *tmp2);
void	sort_export(t_blist **export);
void	print_export(t_blist *export);
void	ft_print_sort(t_shell *shell);
void	copy_env_to_export(t_shell *shell, t_blist *envs);
int		ft_error_message_export(t_shell *shell, char *str);
int		ft_check_arguments_export(t_shell *shell, char *str);
char	*ft_strndup(const char *s, int n);
#endif