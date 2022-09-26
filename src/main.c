#include "minishell.h"
#include "signals.h"
#include "scanner.h"
#include "parser.h"
#include "blists.h"
#include "linked_lists.h"
#include "builtins.h"
#include "executor.h"
#include "clean.h"

int	perror_lexer(t_shell *shell)
{
	char	*s1;

	s1 = ft_strjoin("minishell", ": ");
	ft_putstr_fd(s1, 2);
	free(s1);
	ft_putstr_fd(": lexer error\n", 2);
	shell->exit_status = 1;
	return (shell->exit_status);
}

t_node	*parse_str_function(char *str, t_shell *sh)
{
	t_src		src;
	t_token		*head;
	t_l_list	*list;
	t_node		*cmd;

	src.s = ft_strdup(str);
	src.curpos = 0;
	src.len = ft_strlen(src.s);
	head = tokenize(&src);
	if (!head)
	{
		perror_lexer(sh);
		exit(sh->exit_status);
	}
	list = ll_new((t_blist *)head);
	cmd = parse(list, sh);
	free(src.s);
	ll_drop(list);
	return (cmd);
}

void	fill_starting_values(t_shell	*shell, char **envp)
{
	shell->exit_status = 0;
	shell->pid = getpid();
	env_parsing(envp, &shell->envs);
	env_to_arr(envp, shell);
	signals_start();
}

void	main_helper(char *str, t_node	*cmd, t_shell	*shell)
{
	add_history(str);
	cmd = parse_str_function(str, shell);
	free(str);
	if (cmd->type != error_node)
		executor(cmd, shell);
	node_drop(cmd);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*str;
	t_node	*cmd;

	(void)argc;
	(void)argv;
	ft_memset(&cmd, 0, sizeof(cmd));
	ft_memset(&shell, 0, sizeof(shell));
	fill_starting_values(&shell, envp);
	while (1)
	{
		str = readline("minishell $ ");
		if (str && str[0] == '\0')
			continue ;
		else if (!str)
		{
			printf("\033[Aminishell $ exit\n");
			exit(0);
		}
		main_helper(str, cmd, &shell);
	}
	clean_shell_data(&shell);
	return (0);
}
