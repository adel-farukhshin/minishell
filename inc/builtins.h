#ifndef BUILTINS_H
# define BUILTINS_H

#include "minishell.h"
// For pwd command
// # include <sys/syslimits.h> // PATH_MAX
# include <limits.h>
# include <unistd.h>// getcwd получает путь и копирует его в строку 
# include <stdio.h>

void	env_cmd(t_envs *envs);
void	pwd_cmd(void);
void    cd_cmd(t_shell   *shell);
// int	echo_cmd(char	**args);
#endif