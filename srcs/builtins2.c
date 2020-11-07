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

	j = 0;
	if (ft_strchr(c->arg[i], '='))
	{
		while (c->arg[i][j])
		{
			if (c->arg[i][j] == '=')
			{
				if ((!(ft_export_check_id(c->arg[i], j, &fix))) ||
				(c->arg[i][j - 1] == '_' && j == 1))
					return (2);
				if (!(fix.env = ft_replace_env(c->arg[i], j)))
					return (0);
				break ;
			}
			j++;
		}
	}
	else
		return (3);
	return (1);
}

int		ft_export(t_command *c, int fd)
{
	int		i;
	int		ret;

	if (!c->arg[1])
		return (ft_export_without_arg(&fix, fd));
	i = 1;
	while (c->arg[i])
	{
		if ((ret = ft_export_egal(c, i)) == 0 || ret == 2)
			return (ret);
		if (ret == 3)
		{
			if (ft_env_compare(c->arg[i],\
ft_strlen(c->arg[i])) == ft_env_len(&fix))
			{
				if (!(fix.env = ft_replace_env(c->arg[i],\
ft_strlen(c->arg[i]))))
					return (0);
			}
		}
		i++;
	}
	return (1);
}

int		ft_unset(t_command *c, int fd)
{
	int		i;

	i = 1;
	while (c->arg[i])
	{
		if (ft_export_check_id(c->arg[i], ft_strlen(c->arg[i]), &fix) &&
		(ft_env_len(&fix) != ft_env_compare(c->arg[i], ft_strlen(c->arg[i]))))
		{
			if (!(c->arg[i][0] == '_' && c->arg[i][1] == '\0'))
			{
				if (!(fix.env = ft_unset_env(&fix, c->arg[i])))
					return (0);
			}
		}
		i++;
	}
	return (1);
}

int		ft_cd(t_command *c, int fd)
{
	int		ret;
	char	buf[PATH_MAX];

	if (!c->arg[1])
		ret = chdir("/home/user42");
	else
		ret = chdir(c->arg[1]);
	if (ret == -1)
	{
		fix.error = 1;
		ft_error(errno);
		return (2);
	}
	if (!(getcwd(buf, PATH_MAX)))
	{
		ft_error(errno);
		return (0);
	}
	if (!(fix.env = ft_realloc_env(&fix, buf)))
	{
		ft_error(errno);
		return (0);
	}
	return (1);
}
