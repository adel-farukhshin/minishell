#include "executor.h"
#include "clean.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
        if (access(command, 0) == 0)
			return (command);            
        free (command);
		paths++;
	}
	return (NULL);
}

int    executor(t_node *cmd, t_shell    *shell)
{
    t_context   ctx;
    int children;
    int i;
    int builtin_num;
    int status;

    i = 0;
    ctx.fd[0] = STDIN_FILENO;
    ctx.fd[1] = STDOUT_FILENO;
    ctx.fd_close = -1;
    checking_heredoc(cmd);
    if (cmd->type == cmd_node)
    {
        builtin_num = check_builtins(cmd);
        if (builtin_num != BUILTIN_NONE)
            exe_one_builtin(cmd, &ctx, shell, builtin_num);
        else
        {
            children = execute_cmd(cmd, &ctx, shell);
            while (i < children)
            {
                wait(&status);
                shell->exit_status = WEXITSTATUS(status);
                i++;
            }
        }
    }
    else
    {
        children = exec_node(cmd, &ctx, shell);
        while (i < children)
        {
            wait(&status);
            shell->exit_status = WEXITSTATUS(status);
            i++;
        }
    }
    return (children);
}

int    exec_node(t_node *cmd, t_context   *ctx, t_shell    *shell)
{
    if (cmd->type == error_node)
    {
        printf("error: %s\n", cmd->value.error_msg);
        return (0);
    }
	else if (cmd->type == cmd_node)
        return (execute_cmd(cmd, ctx, shell));
	else
        return (execute_pipe(cmd, ctx, shell));
        
}

int    execute_cmd(t_node    *cmd, t_context *ctx, t_shell    *shell)
{
    pid_t pid;
    char    *path_str;
    char    *exe_cmd;
    char    **cmd_paths;
    char    **cmd_args;
    int     builtin_num;

    // signal(SIGINT, SIG_IGN);
	// signal(SIGQUIT, SIG_IGN);
    pid = fork();
    if (pid == 0)
    {
        make_redir(cmd, ctx);
        dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO);
        dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO);
        if (ctx->fd_close >= 0) 
            close(ctx->fd_close);
        builtin_num = check_builtins(cmd);
        if (builtin_num == BUILTIN_NONE)
        {
            path_str = find_path(shell->env_arr);
            cmd_paths = ft_split(path_str, ':');
            exe_cmd = get_cmd(cmd_paths, (char *)cmd->value.cmd_val.args->val); // почистить
            if (exe_cmd == NULL)
                exe_cmd = (char *)cmd->value.cmd_val.args->val;
            cmd_args = lst_to_char(&cmd->value.cmd_val.args); // почистить
            shell->exit_status = execve(exe_cmd, cmd_args, shell->env_arr);
            if (errno != 0)
            {
                // ft_putstr_fd()
                // perror("exe_cmd"); // ft_putstr_fd();
                if (shell->exit_status == -1)
                    shell->exit_status = 127;
                exit(shell->exit_status);
            }
            clean_array(cmd_args);
            clean_array(cmd_paths);
            free(path_str);
            free(exe_cmd);
            exit(shell->exit_status);
        }
        else
            start_buitins_child(cmd, shell, builtin_num);
    }
    return (1); // One child was spawned
}

int    execute_pipe(t_node    *cmd, t_context *ctx, t_shell    *shell)
{
    t_node  *left;
    t_node  *right;
    int ft_pipe[2];
    t_context   left_ctx;
    t_context   right_ctx;
    int children;
    
    pipe(ft_pipe);
    children = 0;
    left = cmd->value.pipe_val.left;
    left_ctx = *ctx;
    left_ctx.fd[STDOUT_FILENO] = ft_pipe[STDOUT_FILENO];
    left_ctx.fd_close = ft_pipe[STDIN_FILENO];
    children += exec_node(left, &left_ctx, shell);
    close(ft_pipe[STDOUT_FILENO]);
    right = cmd->value.pipe_val.right;
    right_ctx = *ctx;
    right_ctx.fd[STDIN_FILENO] = ft_pipe[STDIN_FILENO];
    right_ctx.fd_close = ft_pipe[STDOUT_FILENO];
    children += exec_node(right, &right_ctx, shell);
    close(ft_pipe[STDIN_FILENO]);
    return (children);
}
