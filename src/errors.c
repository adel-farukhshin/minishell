#include "minishell.h"
#include "executor.h"

int	perror_file(t_shell *shell, char *filename)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin("minishell: ", "\b\b: ");
	s2 = ft_strjoin(s1, filename);
	free(filename);
	free(s1);
	perror(s2);
	free(s2);
	shell->exit_status = errno;
	return (shell->exit_status);
}

void	print_shell(char *str, char *shell)
{
	if (str != NULL)
		ft_putstr_fd(str, 2);
	write(2, shell, ft_strlen(shell));
	write(2, "\b\b", 2);
}

void	perror_exit(char *str, int error)
{
	if (str != NULL)
		perror(str);
	exit(error);
}
