#include "executor.h"

char	*read_heredoc(char *stop_word, int counter)
{
	char	*buf;
	char	*pre_res;
	char	*result;
	int		file;
	char	*filename;
	char	*counter_str;

	counter_str = ft_itoa(counter);
	filename = ft_strjoin(".heredoc_tmp", counter_str);
	file = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file < 0)
		printf("Error!!!");
	buf = NULL;
	result = ft_strdup("");
	while (1)
	{
		write(1, "> ", 2);
		buf = get_next_line(0);
		pre_res = result;
		if (!ft_strncmp(buf, stop_word, ft_strlen(stop_word)))
			break ;
		result = ft_strjoin(pre_res, buf);
		free(buf);
		free(pre_res);
	}
	write(file, result, ft_strlen(result));
	free(result);
	free(buf);
	free(counter_str);
	return (filename);
}

void	checking_heredoc(t_node	*cmd)
{
	t_blist *redir_list;
	static int counter;
	char *new_filename;

	if (cmd->type == cmd_node)
	{
		redir_list = cmd->value.cmd_val.redirs;
   		if (redir_list == NULL)
		{
			return ;
		}
		while (redir_list)
    	{
			if (*(char *)redir_list->key == R_INS)
			{
				new_filename = read_heredoc(redir_list->val, counter);
				printf("Here: %s\n", (char *)redir_list->val);
				free(redir_list->val);
				redir_list->val = (void *)new_filename;
				counter++;
			}
			redir_list = redir_list->next;		
		}
	}
	else
	{
		checking_heredoc(cmd->value.pipe_val.left);
		checking_heredoc(cmd->value.pipe_val.right);
	}
	
}

void    read_redirect(char *file_name, t_context *ctx)
{
    int fd_in;

    fd_in = open(file_name, O_RDONLY);
    if (fd_in < 0)
    {
        ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd("\n", 2);
		exit(1); // правильно поставить exit 
    }
    dup2(fd_in, ctx->fd[STDIN_FILENO]);
	close(fd_in);
}

void    write_redirect(char *file_name, int flag, t_context *ctx)
{
    int	fd_out;

	if (flag == 6)
		fd_out = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (flag == 8)
		fd_out = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644); // дозапись 
	else
		return ;
    dup2(fd_out, ctx->fd[STDOUT_FILENO]);
	close(fd_out);
}

int	make_redir(t_node    *cmd, t_context *ctx)
{
	t_blist *redir_list;
    
	redir_list = cmd->value.cmd_val.redirs;
    if (redir_list == NULL)
		return (0);
	while (redir_list)
    {
		if (*(char *)redir_list->key == R_OUT)
			write_redirect((char *)redir_list->val, R_OUT, ctx);
		if (*(char *)redir_list->key == R_IN || *(char *)redir_list->key == R_INS)
		{
			read_redirect((char *)redir_list->val, ctx);
			if (*(char *)redir_list->key == R_INS)
			{
				unlink((char *)redir_list->val);
				printf("HEREDOC %s\n", (char *)redir_list->val);
				free((char *)redir_list->val);
			}
		}
		if (*(char *)redir_list->key == R_APP)
			write_redirect((char *)redir_list->val, R_APP, ctx);
		redir_list = redir_list->next;
	}
	return (1);
}
