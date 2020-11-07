/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:24:18 by aduchemi          #+#    #+#             */
/*   Updated: 2020/07/15 16:59:40 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_exit(t_f *g_f, char *line, int e)
{
	free(line);
	ft_exit_f(g_f, -2, e);
}

t_command	*ft_free_part_command(t_command *c, int i)
{
	if (i >= 1)
		free(c->n_input);
	if (i >= 2)
		free(c->n_out);
	if (i >= 3)
		free(c->arg);
	if (i >= 4)
		free(c->arg[0]);
	free(c);
	return (NULL);
}

void		ft_del_command(void *c)
{
	ft_free_command(c);
}

void		ft_free_command(t_command *c)
{
	int i;

	free(c->n_out);
	free(c->n_input);
	i = 0;
	while (c->arg[i])
	{
		free(c->arg[i]);
		i++;
	}
	free(c->arg);
	free(c);
}

int			ft_exit_f(t_f *g_f, int i, int e)
{
	int t;
	int k;

	k = g_f->exit;
	if (i == -2)
	{
		i = 0;
		while (g_f->env && g_f->env[i])
			i++;
	}
	t = 0;
	while (t < i)
	{
		free(g_f->env[t]);
		t++;
	}
	free(g_f->env);
	exit(e);
}
