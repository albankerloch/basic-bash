/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:15:37 by aduchemi          #+#    #+#             */
/*   Updated: 2020/11/06 22:20:21 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_add_list(t_list *t)
{
	t_command	*c;
	t_list		*new;

	if (!(c = ft_command_construct()))
		return (0);
	if (!(new = ft_lstnew(c)))
	{
		ft_free_command(c);
		return (0);
	}
	ft_lstadd_back(&t, new);
	return (1);
}

t_list		*ft_init_list(void)
{
	t_list		*t;
	t_command	*c;

	if (!(c = ft_command_construct()))
		return (NULL);
	if (!(t = ft_lstnew(c)))
	{
		ft_free_command(c);
		free(t);
		return (NULL);
	}
	return (t);
}

t_command	*ft_command_construct(void)
{
	t_command	*c;

	if (!(c = malloc(sizeof(t_command))))
		return (ft_free_part_command(c, 0));
	c->input = 0;
	if (!(c->n_input = malloc(sizeof(char *))))
		return (ft_free_part_command(c, 1));
	c->n_input[0] = '\0';
	c->add = 0;
	c->quote = 0;
	if (!(c->n_out = malloc(sizeof(char *))))
		return (ft_free_part_command(c, 2));
	c->n_out[0] = '\0';
	if (!(c->arg = malloc(sizeof(char **) * 2)))
		return (ft_free_part_command(c, 3));
	if (!(c->arg[0] = malloc(sizeof(char *))))
		return (ft_free_part_command(c, 4));
	c->arg[0][0] = '\0';
	c->arg[1] = NULL;
	c->k = -1;
	return (c);
}

void		ft_f_construct(t_f *g_f, char **envp, int argc, char *argv[])
{
	int		len;

	(void)argc;
	(void)argv;
	g_f->line = NULL;
	len = 0;
	while (envp && envp[len])
		len++;
	if (!(g_f->env = malloc(sizeof(char **) * (len + 1))))
		ft_exit_f(g_f, -1, EXIT_FAILURE);
	len = 0;
	while (envp && envp[len])
	{
		if (!(g_f->env[len] = ft_strdup(envp[len])))
			ft_exit_f(g_f, len, EXIT_FAILURE);
		len++;
	}
	g_f->env[len] = NULL;
	g_f->error = 0;
	g_f->exit = -1;
}
