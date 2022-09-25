#include "builtins.h"
#include "executor.h"
#include "clean.h"

void start_buitins_parent(t_node    *cmd, t_shell   *shell, int builtin_num)
{
    char    **cmd_args;
    char    *cmd_str;

    cmd_str = (char *)cmd->value.cmd_val.args->val;
    if (cmd_str != NULL)
    {
        cmd_args = lst_to_char(&cmd->value.cmd_val.args);
        if (builtin_num == BUILTIN_CD)
            cd_cmd(shell, cmd_args);
        if (builtin_num == BUILTIN_EXIT)
            exit_cmd(shell, cmd_args);
        if (builtin_num == BUILTIN_EXPORT)
            export_cmd(shell, cmd_args);
        if (builtin_num == BUILTIN_UNSET)
            unset_cmd(shell, shell->envs, cmd_args);
        if (builtin_num == BUILTIN_ECHO)
            echo_cmd(shell, cmd_args);
        if (builtin_num == BUILTIN_PWD)
            pwd_cmd(shell);
        if (builtin_num == BUILTIN_ENV)
            env_cmd(shell);
    }
    clean_array(cmd_args);
}

void start_buitins_child(t_node    *cmd, t_shell   *shell, int builtin_num)
{
    char    **cmd_args;
    char    *cmd_str;

    cmd_str = (char *)cmd->value.cmd_val.args->val;
    if (cmd_str != NULL)
    {
        if (builtin_num == BUILTIN_CD)
        {
            cmd_args = lst_to_char(&cmd->value.cmd_val.args);
            cd_cmd(shell, cmd_args);
            exit(0);
        }
        if (builtin_num == BUILTIN_EXIT)
        {
            cmd_args = lst_to_char(&cmd->value.cmd_val.args);
            exit_cmd(shell, cmd_args);
        }
        if (builtin_num == BUILTIN_EXPORT)
        {
            cmd_args = lst_to_char(&cmd->value.cmd_val.args);
            export_cmd(shell, cmd_args);
            exit(0);
        }
        if (builtin_num == BUILTIN_UNSET)
        {
            cmd_args = lst_to_char(&cmd->value.cmd_val.args);
            unset_cmd(shell, shell->envs, cmd_args);
            exit(0);
        }
        if (builtin_num == BUILTIN_ECHO)
        {
            cmd_args = lst_to_char(&cmd->value.cmd_val.args);
            echo_cmd(shell, cmd_args);
            exit(0);
        }
        if (builtin_num == BUILTIN_PWD)
        {
            pwd_cmd(shell);
            exit(0);
        }
        if (builtin_num == BUILTIN_ENV)
        {
            env_cmd(shell);
            exit(0);
        }
    }
    clean_array(cmd_args);
}

int check_builtins(t_node *cmd)
{
    char    *cmd_str;

    cmd_str = (char *)cmd->value.cmd_val.args->val;
    if (cmd_str != NULL)
    {
        if (!ft_strncmp(cmd_str, "cd", 2 ) || !ft_strncmp(cmd_str, "CD", 2))
            return (BUILTIN_CD);
        if (!ft_strncmp(cmd_str, "exit", 4) || !ft_strncmp(cmd_str, "EXIT", 4))
            return (BUILTIN_EXIT);
        if (!ft_strncmp(cmd_str, "export", 6) || !ft_strncmp(cmd_str, "EXPORT", 6))
            return (BUILTIN_EXPORT);
        if (!ft_strncmp(cmd_str, "unset", 5) || !ft_strncmp(cmd_str, "UNSET", 5))
            return (BUILTIN_UNSET);
        if (!ft_strncmp(cmd_str, "echo", 5) || !ft_strncmp(cmd_str, "ECHO", 5))
            return (BUILTIN_ECHO);
        if (!ft_strncmp(cmd_str, "pwd", 5) || !ft_strncmp(cmd_str, "PWD", 5))
            return (BUILTIN_PWD);
        if (!ft_strncmp(cmd_str, "env", 5) || !ft_strncmp(cmd_str, "ENV", 5))
            return (BUILTIN_ENV);
    }
    return (BUILTIN_NONE);
}

int	save_fd(int fd[2])
{
    fd[STDIN_FILENO] = dup(STDIN_FILENO);
	if (fd[STDIN_FILENO] == -1)
		return (0);
	fd[STDOUT_FILENO] = dup(STDOUT_FILENO);
	if (fd[STDOUT_FILENO] == -1)
	{
		close(fd[STDIN_FILENO]);
		return (0);
	}
	return (1);
}

int	restore_fd(int fd[2])
{
	int error;

	error = 0;
	if (dup2(fd[STDIN_FILENO], STDIN_FILENO) == -1)
		error = 1;
	if (dup2(fd[STDOUT_FILENO], STDOUT_FILENO) == -1)
		error = 1;
	if (error)
		return (0);
	return (1);
}

void	delete_saved_fd(int fd[2])
{
	if (fd[STDIN_FILENO] != -1)
		close(fd[STDIN_FILENO]);
	if (fd[STDOUT_FILENO] != -1)
		close(fd[STDOUT_FILENO]);
}

void  exe_one_builtin(t_node *cmd, t_context   *ctx, t_shell    *shell, int builtin_num)
{
    int fd[2];

    if (!save_fd(fd))
    {
        printf("ERROR!");
    }
    make_redir(cmd, ctx);
    start_buitins_parent(cmd, shell,builtin_num);
    if (!restore_fd(fd))
    {
        delete_saved_fd(fd);
        printf("ERROR!");
    }
    delete_saved_fd(fd);
}






































// void start_builtins(void    *cmd, t_shell   *shell)
// {
//     (void)shell;
//     if (!ft_strncmp((char *)cmd, "cd", 2 ) || !ft_strncmp((char *)cmd, "CD", 2))
//     {
//         printf("%s", "cd");
//         // my_cd();
//     }
//     if (!ft_strncmp((char *)cmd, "exit", 4) || !ft_strncmp((char *)cmd, "EXIT", 4))
//     {
//         printf("%s", "exit");
//         // my_exit(cmd, shell);
//     }
//     if (!ft_strncmp((char *)cmd, "export", 6) || !ft_strncmp((char *)cmd, "EXPORT", 6))
//     {
//         printf("%s", "export");
//         // my_export();
//     }   
//     if (!ft_strncmp((char *)cmd, "unset", 5) || !ft_strncmp((char *)cmd, "UNSET", 5))
//     {
//         printf("%s", "unset");
//         // my_unset();
//     }
        
// }