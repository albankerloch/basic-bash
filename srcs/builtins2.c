/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:36:55 by aduchemi          #+#    #+#             */
/*   Updated: 2020/11/07 13:54:31 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_export_egal(t_command *c, int i)
{
	int		j;

	if (ft_strchr(c->arg[i], '='))
	{
		j = 0;
		while (c->arg[i][j])
		{
			if (c->arg[i][j] == '=')
			{
				if ((!(ft_export_check_id(c->arg[i], j))) ||
				(c->arg[i][0] == '_' && j == 1))
					return (2);
				if (!(g_f.env = ft_replace_env(c->arg[i], j)))
					return (0);
				return (1);
			}
			j++;
		}
	}
	return (3);
}

int		ft_export(t_command *c, int fd)
{
	int		i;
	int		ret;

	if (!c->arg[1])
		return (ft_export_without_arg(&g_f, fd));
	i = 1;
	while (c->arg[i])
	{
		if ((ret = ft_export_egal(c, i)) == 0)
			return (ret);
		if (ret == 3 && ft_export_check_id(c->arg[i],\
ft_strlen(c->arg[i])))
		{
			if (ft_env_compare(c->arg[i],\
ft_strlen(c->arg[i])) == ft_env_len(&g_f))
			{
				if (!(g_f.env = ft_replace_env(c->arg[i],\
ft_strlen(c->arg[i]))))
					return (0);
			}
		}
		i++;
	}
	return (g_f.error == 1 ? 2 : 1);
}

int		ft_unset(t_command *c)
{
	int		i;

	i = 1;
	while (c->arg[i])
	{
		if (ft_export_check_id(c->arg[i], ft_strlen(c->arg[i])) &&
		(ft_env_len(&g_f) != ft_env_compare(c->arg[i], ft_strlen(c->arg[i]))))
		{
			if (!(c->arg[i][0] == '_' && c->arg[i][1] == '\0'))
			{
				if (!(g_f.env = ft_unset_env(&g_f, c->arg[i])))
					return (0);
			}
		}
		i++;
	}
	return (g_f.error == 1 ? 2 : 1);
}

int		ft_cd(t_command *c)
{
	char	buf[PATH_MAX];

	if (!c->arg[1] || c->arg[2])
	{
		ft_cmd_error("bash", "cd needs one argument");
		return (2);
	}
	if (chdir(c->arg[1]) == -1)
	{
		g_f.error = 1;
		ft_cmd_error_errno("bash", "cd", c->arg[1], errno);
		return (2);
	}
	if (!(getcwd(buf, PATH_MAX)))
	{
		ft_error(errno);
		return (0);
	}
	if (!(g_f.env = ft_realloc_env(&g_f, buf)))
	{
		ft_error(errno);
		return (0);
	}
	return (1);
}
