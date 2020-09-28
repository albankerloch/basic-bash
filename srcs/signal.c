#include "../includes/minishell.h"

void ft_sig_handler(int signum)
{
  if (signum == SIGINT)
	{
		ft_putchar('\n');
		ft_putstr("<minishell> ");
		signal(SIGINT, ft_sig_handler);
	}
}

void ft_sig_handler_process(int signum)
{
  if (signum == SIGINT)
	{
		ft_putchar('\n');
		signal(SIGINT, ft_sig_handler_process);
	}
}

void    ft_init_signal(int nb)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	//signal(SIGWINCH, ft_sigwinch_handler);
	signal(SIGINT, ft_sig_handler);
}