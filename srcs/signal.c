/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:13:12 by aduchemi          #+#    #+#             */
/*   Updated: 2020/11/06 22:13:14 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_f.error = 130;
		g_f.line[0] = '\0';
		ft_putchar('\n');
		ft_putstr("<minishell> ");
	}
	else if (signum == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 2);
}

void	ft_sig_handler_process(int signum)
{
	if (signum == SIGINT)
	{
		g_f.error = 130;
		ft_putchar('\n');
	}
	else if (signum == SIGQUIT)
	{
		g_f.error = 131;
		ft_putstr_fd("Quitter (core dumped)\n", 2);
	}
}
