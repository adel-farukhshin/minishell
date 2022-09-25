#ifndef BUILTINS_H
# define BUILTINS_H

#include "minishell.h"
// For pwd command
# include <sys/syslimits.h> // PATH_MAX
# include <unistd.h>// getcwd получает путь и копирует его в строку 
# include <stdio.h>

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

int check_builtins(t_node *cmd);
void start_buitins_parent(t_node    *cmd, t_shell   *shell, int builtin_num);
void start_buitins_child(t_node    *cmd, t_shell   *shell, int builtin_num);
void exe_one_builtin(t_node *cmd, t_context   *ctx, t_shell    *shell, int builtin_num);
void    cd_cmd(t_shell    *shell, char **cmd_args);
void	env_cmd(t_shell	*shell);
void	pwd_cmd(t_shell	*shell);
void    echo_cmd(t_shell    *shell, char **cmd_args);
void	exit_cmd(t_shell *shell, char **cmd_args);
void	unset_cmd(t_shell    *shell, t_blist *envp, char **cmd_args);
void	export_cmd(t_shell *shell, char **cmd_args);

#endif