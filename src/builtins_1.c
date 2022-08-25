#include "minishell.h"
#include "builtins.h"

void	env_cmd(t_envs *envs)
{
	while (envs)
	{
		printf("%s=%s\n", envs->key, envs->value);
		envs = envs->next;
	}
	exit(0);
}

void	pwd_cmd(void)
{
	char	pwd[PATH_MAX + 1];

	if (!getcwd(pwd, PATH_MAX + 1))
		printf("ERROR");
	printf("%s\n", pwd);
	exit(0);
}