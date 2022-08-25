#include "builtins.h"

void start_builtins(void    *cmd, t_shell   *shell)
{
    (void)shell;
    if (!ft_strncmp((char *)cmd, "cd", 2 ) || !ft_strncmp((char *)cmd, "CD", 2))
    {
        printf("%s", "cd");
        // my_cd();
    }
    if (!ft_strncmp((char *)cmd, "exit", 4) || !ft_strncmp((char *)cmd, "EXIT", 4))
    {
        printf("%s", "exit");
        // my_exit(cmd, shell);
    }
    if (!ft_strncmp((char *)cmd, "export", 6) || !ft_strncmp((char *)cmd, "EXPORT", 6))
    {
        printf("%s", "export");
        // my_export();
    }   
    if (!ft_strncmp((char *)cmd, "unset", 5) || !ft_strncmp((char *)cmd, "UNSET", 5))
    {
        printf("%s", "unset");
        // my_unset();
    }
        
}

int checking_buitins(void   *cmd, t_shell   *shell)
{
    int exit_status;

    if (!ft_strncmp((char *)cmd, "cd", 2 ) || !ft_strncmp((char *)cmd, "CD", 2))
        exit_status = 1;
    if (!ft_strncmp((char *)cmd, "exit", 4) || !ft_strncmp((char *)cmd, "EXIT", 4))
       exit_status = 2;
    if (!ft_strncmp((char *)cmd, "export", 6) || !ft_strncmp((char *)cmd, "EXPORT", 6))
        exit_status = 3;
    if (!ft_strncmp((char *)cmd, "unset", 5) || !ft_strncmp((char *)cmd, "UNSET", 5))
        exit_status = 4;
     if (!ft_strncmp((char *)cmd, "echo", 5) || !ft_strncmp((char *)cmd, "ECHO", 5))
        exit_status = 5;
     if (!ft_strncmp((char *)cmd, "pwd", 5) || !ft_strncmp((char *)cmd, "PWD", 5))
        exit_status = 6;
     if (!ft_strncmp((char *)cmd, "env", 5) || !ft_strncmp((char *)cmd, "ENV", 5))
        exit_status = 7;
    if (exit_status > 0 && exit_status < 5)
    {
        start_builtins(cmd, shell);
        return (-1);
    }
    return (0);
}








































// int	exit_status;

// 	exit_status = 0;
// 	if (!str)
// 		return (exit_status);
// 	if (!(ft_strncmp(str, "cd", 2)) && (str[2] == ' ' || str[2] == 0))
// 		exit_status = 1;
// 	if (!(ft_strncmp(str, "echo", 4)) && (str[4] == ' ' || str[4] == 0))
// 		exit_status = 5;
// 	if (!(ft_strncmp(str, "env", 3)) && (str[3] == ' ' || str[3] == 0))
// 		exit_status = 6;
// 	if (!(ft_strncmp(str, "exit", 4)) && (str[4] == ' ' || str[4] == 0))
// 		exit_status = 2;
// 	if (!(ft_strncmp(str, "export", 6)) && (str[6] == ' ' || str[6] == 0))
// 		exit_status = 3;
// 	if (!(ft_strncmp(str, "pwd", 3)) && (str[3] == ' ' || str[3] == 0))
// 		exit_status = 7;
// 	if (!(ft_strncmp(str, "unset", 5)) && (str[5] == ' ' || str[5] == 0))
// 		exit_status = 4;
// 	if ((exit_status < 5 && exit_status > 0) || (flag && exit_status > 4))
// 		return (execute_builtins(m_shell, str, exit_status));
// 	return (0);