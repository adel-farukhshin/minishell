#include "executor.h"
#include "lists.h"

#include <sys/types.h>
#include <sys/wait.h>

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

    i = 0;
    ctx.fd[0] = STDIN_FILENO;
    ctx.fd[1] = STDOUT_FILENO;
    ctx.fd_close = -1;
    
    children = exec_node(cmd, &ctx, shell);
    while (i < children)
    {
        // ft_putstr_fd("HERE!", 2);
        // printf("%d\n", i);
        wait(NULL);
        i++;
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

    path_str = find_path(shell->env_arr);
    cmd_paths = ft_split(path_str, ':');
    pid = fork();
    if (pid == 0)
    {
        dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO);
        dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO);
        if (ctx->fd_close >= 0) 
            close(ctx->fd_close);
        exe_cmd = get_cmd(cmd_paths, (char *)cmd->value.cmd_val.args->val); // почистить
        cmd_args = lst_to_char(&cmd->value.cmd_val.args); // почистить
        execve(exe_cmd, cmd_args, shell->env_arr);
        ft_putstr_fd("ERROR!", 2);
        exit(1);
            // global.int_status = execve(args[0], args, NULL);
    }
    return (1); // One child was spawned
}

int    execute_pipe(t_node    *cmd, t_context *ctx, t_shell    *shell)
{
    t_node  *left;
    t_node  *right;
    int p[2];
    t_context   lft_ctx;
    t_context   right_ctx;
    int children;
    
    pipe(p);
    children = 0;
    left = cmd->value.pipe_val.left;
    lft_ctx = *ctx;
    lft_ctx.fd[STDOUT_FILENO] = p[STDOUT_FILENO];
    lft_ctx.fd_close = p[STDIN_FILENO];
    children += exec_node(left, &lft_ctx, shell);
    close(p[STDOUT_FILENO]);

    right = cmd->value.pipe_val.right;
    right_ctx = *ctx;
    right_ctx.fd[STDIN_FILENO] = p[STDIN_FILENO];
    right_ctx.fd_close = p[STDOUT_FILENO];
    children += exec_node(right, &right_ctx, shell);
    
    close(p[STDIN_FILENO]);
    return (children);
}



    // ручное заполнение 
    // char *args[3];
    //     args[0] = (char *)cmd->value.cmd_val.args->val;
    //     if (cmd->value.cmd_val.args->next)
    //         args[1] = (char *)cmd->value.cmd_val.args->next->val;
    //     else
    //         args[1] = NULL;
    //     args[2] = NULL;
    //     execve(args[0], args, NULL);

     //  execvp(args[0], args);
            // int errnum = errno;
            // perror(strerror(errnum));
