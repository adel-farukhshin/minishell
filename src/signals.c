#include "signals.h"

void	func_ctr_c(int sign)
{
	(void)sign;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signals_start(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &func_ctr_c);
}
