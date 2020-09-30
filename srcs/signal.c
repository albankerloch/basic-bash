#include "../includes/minishell.h"

void ft_sig_handler(int signum)
{
	ft_putchar('\n');
	ft_putstr("<minishell> ");
}

void ft_sig_handler_quit(int signum)
{
	ft_putstr("AA\n");
	printf("signum : %d\n", signum);
}

void ft_sig_handler_process(int signum)
{
  if (signum == SIGINT)
	{
		ft_putchar('\n');
		signal(SIGINT, ft_sig_handler_process);
	}
	if (signum == SIGQUIT)
	{
		ft_putchar('\n');
	}
}

/*
		signal(SIGINT, ft_sig_handler);
		signal(SIGQUIT, ft_sig_handler_quit);
		signal(SIGHUP, ft_sig_handler_quit);
		signal(SIGILL, ft_sig_handler_quit);
		signal(SIGTRAP, ft_sig_handler_quit);
		signal(SIGABRT, ft_sig_handler_quit);
		signal(SIGFPE, ft_sig_handler_quit);
		signal(SIGUSR1, ft_sig_handler_quit);	
		signal(SIGTERM, ft_sig_handler_quit);
		signal(SIGTTIN, ft_sig_handler_quit);	
		signal(SIGTTOU, ft_sig_handler_quit);	
		signal(SIGTSTP, ft_sig_handler_quit);
		signal(SIGUSR2, ft_sig_handler_quit);	
		signal(SIGWINCH, ft_sig_handler_quit);	
		*/