#include "minishell.h"
#include "signals.h"
#include "scanner.h"
#include "parser.h"
#include "blists.h"
#include "linked_lists.h"
#include "builtins.h"
#include "executor.h"

t_node	*parse_str_function(char	*str)
{
	t_src	src;
	t_token	*head;
	t_l_list	*list;
	t_node *cmd;

	// (void)shell;
	// Create src
	src.s = malloc(sizeof(char *) * ft_strlen(str));
	src.s = ft_strdup(str);
	src.curpos = 0;
	src.len = ft_strlen(src.s);
	// printf("Source: %s\n", src.s);
	// Create tokens' list
	head = tokenize(&src);
	free(src.s);
	if (!head)
		printf("error\n");
	// turn tokens' list to t_l_list structure
	list= ll_new((t_blist *)head);
	// printf("the head: _%s_\n", (char *)list->head->val);
	cmd = parse(list);
	// print_node(cmd, 0);
	// printf("\n%s\n", (char *)cmd->value.cmd_val.args->next->val);
	return (cmd);
	node_drop(cmd); // free cmd
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
	env_parsing(envp, &shell.envs);
	env_to_arr(envp, &shell);
	while (1)
	{
		signals_start();
		str = readline("minishell $ ");
		if (str && str[0] == '\0') //del
			continue;
		else if (!str)
		{
			printf("\033[Aminishell $ exit\n"); //чекнуть, что надо выводить
			exit(0);
		}
		add_history(str);
		cmd = parse_str_function(str);
		executor(cmd, &shell);
		free(str); // добавить для очистки и почистить shell, shell->env, shell->arr
	}
	return (0);
}

