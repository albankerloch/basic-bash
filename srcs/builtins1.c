/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:36:48 by aduchemi          #+#    #+#             */
/*   Updated: 2020/11/06 22:43:02 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_echo(t_command *c, int fd)
{
	int		i;
	int		n;

	n = 0;
	if (c->arg[1])
	{
		i = 1;
		ft_echo_n(&n, c->arg, &i);
		while (c->arg[i])
		{
			ft_putstr_fd(c->arg[i], fd);
			if (c->arg[i + 1])
				ft_putchar_fd(' ', fd);
			i++;
		}
	}
	if (n == 0)
		ft_putchar_fd('\n', fd);
	return (1);
}

int			ft_env(t_command *c, int fd)
{
	int		j;

	j = 0;
	if (ft_env_err(c) == -1)
		return (2);
	while (g_f.env && g_f.env[j])
	{
		if (ft_strchr(g_f.env[j], '='))
		{
			ft_putstr_fd(g_f.env[j], fd);
			ft_putchar_fd('\n', fd);
		}
		j++;
	}
	if (c->arg[1] && !ft_strcmp(c->arg[1], "="))
		ft_putstr_fd("=\n", fd);
	return (1);
}

int			ft_pwd(int fd)
{
	char	here[PATH_MAX];

	if (!(getcwd(here, PATH_MAX)))
	{
		ft_error_errno("bash", "pwd", errno);
		return (0);
	}
	ft_putstr_fd(here, fd);
	ft_putchar_fd('\n', fd);
	return (1);
}

static void	ft_error_num_arg(char *str)
{
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int			ft_builtin_exit(t_command *c)
{
	ft_putstr("exit\n");
	if (!(c->arg[1]))
		g_f.exit = 0;
	else
	{
		if (!(ft_isnum(c->arg[1])) || (!(ft_check_atoi(c->arg[1]))))
		{
			ft_error_num_arg(c->arg[1]);
			g_f.exit = 2;
			g_f.error = 2;
		}
		else
		{
			if (!(c->arg[2]))
				g_f.exit = (unsigned char)ft_atoi(c->arg[1]);
			else
			{
				ft_putstr_fd("bash: exit: too many arguments\n", 2);
				g_f.error = 1;
				return (2);
			}
		}
	}
	return (0);
}
