/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:24:18 by aduchemi          #+#    #+#             */
/*   Updated: 2020/07/15 16:59:40 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_builtins(t_command *c, int fd)
{
	if (ft_strcmp(c->arg[0], "echo") == 0)
		return (ft_echo(c, fd));
	else if (ft_strcmp(c->arg[0], "env") == 0)
		return (ft_env(c, fd));
	else if (ft_strcmp(c->arg[0], "pwd") == 0)
		return (ft_pwd(fd));
	else if (ft_strcmp(c->arg[0], "export") == 0)
		return (ft_export(c, fd));
	else if (ft_strcmp(c->arg[0], "unset") == 0)
		return (ft_unset(c));
	else if (ft_strcmp(c->arg[0], "cd") == 0)
		return (ft_cd(c));
	else if (ft_strcmp(c->arg[0], "exit") == 0)
		return (ft_builtin_exit(c));
	return (-1);
}
