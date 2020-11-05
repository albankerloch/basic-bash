#include "../includes/minishell.h"

void ft_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		fix.error = 130;
		ft_putchar('\n');
		ft_putstr("<minishell> ");
	}
	else if (signum == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 2);
}

void ft_sig_handler_process(int signum)
{
	if (signum == SIGINT)
	{
		fix.error = 130;
		ft_putchar('\n');
	}
	else if (signum == SIGQUIT)
	{
		fix.error = 131;
		ft_putstr_fd("Quitter (core dumped)\n", 2);
	}
}
