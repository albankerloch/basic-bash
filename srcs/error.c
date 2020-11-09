/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:12:53 by aduchemi          #+#    #+#             */
/*   Updated: 2020/11/06 22:12:54 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cmd_error(char *str, char *message)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" : ", 2);
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	g_f.error = 1;
}

void	ft_custom_error(char *cmd, char *arg, char *message)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
}

int		ft_syntax_error(char *s)
{
	ft_putstr_fd("bash: syntax error near unexpected token \" ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(" \"\n", 2);
	g_f.error = 2;
	return (2);
}
