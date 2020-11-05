/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 22:43:02 by aduchemi          #+#    #+#             */
/*   Updated: 2020/11/05 23:02:11 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_parser(t_list *t, char *line, int *i)
{
	int			k;
	int			ret;
	t_command	*c;

	k = -1;
	while (line[*i])
	{
		if (line[*i] == ' ')
			(*i)++;
		else if (line[*i] == '>')
		{
			if ((ret = ft_redirection_right(t->content, line, i, &fix)) != 1)
				return (ret);
		}
		else if (line[*i] == ';' && c->quote == 0)
		{
			(*i)++;
			return (1);
		}
		else if (line[*i] == '<')
		{
			if ((ret = ft_redirection_left(t->content, line, i, &fix)) != 1)
				return (ret);
		}
		else if (line[*i] == '|')
		{
			if (!(ft_add_list(t, &fix)))
				return (0);
			t = t->next;
			k = -1;
			(*i)++;
		}
		else
		{
			if ((ret = ft_arg(t->content, line, i, &k)) != 1)
				return (ret);
		/*	c = t->content;
			k++;
			if (k != 0)
			{
				if (!(c->arg = ft_realloc_arg(c->arg)))
					return (0);
			}
			if (!(ret = ft_new_arg(c, line, i)))
				return (0);
			if (ret == 2 && ft_strlen(c->arg[k]) == 0)
			{
				free(c->arg[k]);
				c->arg[k] = NULL;
				if (k == 0)
					return (2);
				k--;
			}*/
		}
	}
	if (c->quote != 0)
		ft_putstr_fd("WARNING : Quotes automatically closed\n", 2);
	return (1);
}

int	ft_arg(t_command *c, char *line, int *i, int *k)
{
	int	ret;

	(*k)++;
	if (*k != 0)
	{
		if (!(c->arg = ft_realloc_arg(c->arg)))
			return (0);
	}
	if (!(ret = ft_new_arg(c, line, i)))
		return (0);
	if (ret == 2 && ft_strlen(c->arg[*k]) == 0)
	{
		free(c->arg[*k]);
		c->arg[*k] = NULL;
		if (*k == 0)
			return (2);
		(*k)--;
	}
	return (1);
}