#include "executor.h"

char	*make_file_name(int counter)
{
	char	*counter_str;
	char	*filename;

	counter_str = ft_itoa(counter);
	filename = ft_strjoin(".heredoc_tmp", counter_str);
	free(counter_str);
	return (filename);
}

char	*reading_helper(char *stop_word)
{
	char	*buf;
	char	*pre_res;
	char	*result;

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
	free(buf);
	return (result);
}

char	*read_heredoc(char *stop_word, int counter, t_shell	*shell)
{
	char	*result;
	int		file;
	char	*filename;

	filename = make_file_name(counter);
	file = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file < 0)
		perror_file(shell, filename);
	result = reading_helper(stop_word);
	write(file, result, ft_strlen(result));
	free(result);
	return (filename);
}

void	checking_heredoc_helper(t_node	*cmd, t_shell	*shell)
{
	checking_heredoc(cmd->value.pipe_val.left, shell);
	checking_heredoc(cmd->value.pipe_val.right, shell);
}

void	checking_heredoc(t_node	*cmd, t_shell *shell)
{
	t_blist		*redir_list;
	static int	counter;
	char		*new_filename;

	if (cmd->type == cmd_node)
	{
		redir_list = cmd->value.cmd_val.redirs;
		if (redir_list == NULL)
			return ;
		while (redir_list)
		{
			if (*(char *)redir_list->key == R_INS)
			{
				new_filename = read_heredoc(redir_list->val, counter, shell);
				free(redir_list->val);
				redir_list->val = (void *)new_filename;
				counter++;
			}
			redir_list = redir_list->next;
		}
	}
	else
		checking_heredoc_helper(cmd, shell);
}
