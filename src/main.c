#include "minishell.h"
#include "signals.h"
#include "scanner.h"
#include "parser.h"
#include "blists.h"
#include "linked_lists.h"
#include "builtins.h"
#include "executor.h"
#include "clean.h"

t_node	*parse_str_function(char *str, t_shell *sh)
{
	t_src	src;
	t_token	*head;
	t_l_list	*list;
	t_node *cmd;

	src.s = ft_strdup(str);
	src.curpos = 0;
	src.len = ft_strlen(src.s);
	head = tokenize(&src);
	if (!head)
		printf("error\n");
	list= ll_new((t_blist *)head);
	cmd = parse(list, sh);
	free(src.s);
	ll_drop(list);
	// print_node(cmd, 0);
	return (cmd);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;
	char *str;
	t_node	*cmd;

	(void)argc;
	(void)argv;
	ft_memset(&cmd, 0, sizeof(cmd));
	ft_memset(&shell, 0, sizeof(shell));
	shell.exit_status = 0;
	shell.pid = getpid();
	env_parsing(envp, &shell.envs);
	env_to_arr(envp, &shell);
	signals_start();
	while (1)
	{
		str = readline("minishell $ ");
		if (str && str[0] == '\0')
			continue;
		else if (!str)
		{
			printf("\033[Aminishell $ exit\n"); //чекнуть, что надо выводить
			exit(0);
		}
		add_history(str);
		cmd = parse_str_function(str, &shell);
		free(str);
		executor(cmd, &shell);
		node_drop(cmd);
	}
	clean_shell_data(&shell);
	return (0);
}

