/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_errno.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:12:53 by aduchemi          #+#    #+#             */
/*   Updated: 2020/11/06 22:12:54 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cmd_error_errno(char *str, char *cmd, char *arg, int err)
{
	(void)err;
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
}

void	ft_error_errno(char *cmd, char *arg, int err)
{
	(void)err;
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
}

void	ft_error(int err)
{
	(void)err;
	ft_putstr_fd("Error : ", 2);
	ft_putnbr_fd(errno, 2);
	ft_putchar_fd(' ', 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
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
