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
}

void	ft_custom_error(char *str, char *message)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
}

void	ft_error(int err)
{
	ft_putstr_fd("Error : ", 2);
	ft_putnbr_fd(errno, 2);
	ft_putchar_fd(' ', 2);
	ft_putstr_fd(strerror(errno), 2);
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

char	**ft_free_tab(char **new, int i)
{
	int		k;

	k = 0;
	while (k <= i)
	{
		free(new[k]);
		new[k] = NULL;
		k++;
	}
	free(new);
	new = NULL;
	return (NULL);
}
