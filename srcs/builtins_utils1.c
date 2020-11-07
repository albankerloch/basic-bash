/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:36:17 by aduchemi          #+#    #+#             */
/*   Updated: 2020/11/07 14:00:32 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo_n(int *n, char **arg, int *i)
{
	while (arg[*i])
	{
		if (!ft_strcmp(arg[*i], "-n"))
		{
			*n = 1;
			(*i)++;
		}
		else
			break ;
	}
}

int		ft_env_compare(char *arg, int n)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (g_f.env && g_f.env[j])
	{
		if (ft_strncmp(arg, g_f.env[j], n) == 0 && (g_f.env[j][n] == '=' ||
		g_f.env[j][n] == '\0'))
			i--;
		j++;
		i++;
	}
	return (i);
}

int		ft_env_len(t_f *g_f)
{
	int		len;

	len = 0;
	while (g_f->env[len])
		len++;
	return (len);
}

int		ft_env_err(t_command *c)
{
	if (c->arg[1] && ft_strcmp(c->arg[1], "=") && ft_strcmp(c->arg[1], "-"))
	{
		ft_putstr_fd("env: \"", 2);
		ft_putstr_fd(c->arg[1], 2);
		ft_putstr_fd("\": No such file or directory\n", 2);
		g_f.error = 127;
		return (-1);
	}
	else if (c->arg[1] && !ft_strcmp(c->arg[1], "-"))
	{
		g_f.error = 0;
		return (-1);
	}
	return (1);
}

int		ft_isnum(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] == 45 || (str[i] >= 48 && str[i] <= 57)))
			return (0);
		i++;
	}
	return (1);
}
