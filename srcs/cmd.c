/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 22:43:15 by aduchemi          #+#    #+#             */
/*   Updated: 2020/11/06 21:28:31 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_redir_execve(t_command *c, int fd)
{
	int fdi;

	fdi = 0;
	if (c->add != 0)
	{
		if (dup2(fd, 1) == -1)
		{
			close(fd);
			exit(-1);
		}
	}
	if (c->input == 1)
	{
		if ((fdi = open(c->n_input, O_RDONLY, S_IRUSR | S_IWUSR |
S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) == -1)
			exit(-1);
		if (dup2(fdi, 0) == -1)
		{
			if (c->add != 0)
				close(fd);
			close(fdi);
			exit(-1);
		}
	}
	return (fdi);
}

void	ft_execve(t_command *c, t_f *g_f)
{
	int fd;
	int fdi;

	if ((fd = ft_open_redir(c)) == -1)
		exit(-1);
	fdi = ft_redir_execve(c, fd);
	if (c->arg[0][0] == '/' || (c->arg[0][0] == '.' && c->arg[0][1] && \
c->arg[0][1] == '/') || (ft_env_compare("PATH", 4) == ft_env_len(g_f)))
	{
		if (execve(c->arg[0], c->arg, g_f->env) == -1)
			ft_custom_error("bash", c->arg[0], "No such file or directory");
	}
	else
	{
		if (ft_absolute_path(c) == ft_env_len(g_f))
		{
			ft_cmd_error(c->arg[0], "command not found");
		}
	}
	if (c->add != 0)
		close(fd);
	if (c->input == 1)
		close(fdi);
	exit(127);
}

int		ft_loop_absolute_path(t_command *c, int j, int k,\
char try_path[PATH_MAX])
{
	while (g_f.env && g_f.env[j])
	{
		if (ft_strncmp(g_f.env[j], "PATH", ft_strlen("PATH")) == 0)
		{
			k = 5;
			while (1)
			{
				if (g_f.env[j][k] != ':' && g_f.env[j][k])
					ft_realloc_concat_buff(try_path, g_f.env[j][k]);
				else
				{
					ft_realloc_concat_buff(try_path, '/');
					ft_strjoin_buff(try_path, c->arg[0]);
					execve(try_path, c->arg, g_f.env);
					ft_memset(try_path, '\0', ft_strlen(try_path));
					if (!g_f.env[j][k])
						return (ft_env_len(&g_f));
				}
				k++;
			}
		}
		j++;
	}
	return (j);
}

int		ft_absolute_path(t_command *c)
{
	int		j;
	int		k;
	char	try_path[PATH_MAX];

	j = 0;
	k = 0;
	while (j < PATH_MAX)
	{
		try_path[j] = 0;
		j++;
	}
	j = 0;
	return (ft_loop_absolute_path(c, j, k, try_path));
}
