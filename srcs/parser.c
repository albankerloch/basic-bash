/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 22:43:02 by aduchemi          #+#    #+#             */
/*   Updated: 2020/11/10 14:39:32 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_global_parse(char *line, char *c)
{
	int		i;
	int		quote;
	int		needle;

	i = 0;
	quote = 0;
	needle = 0;
	while (line[i])
	{
		if (ft_len_sub_parse(line, &quote, &needle) == 2)
			return (1);
		if (quote == 0)
		{
			if (!ft_sub_parse(line, i, needle, c))
				return (0);
		}
		needle++;
		i = needle;
	}
	return (1);
}

int		ft_parser_symbol(t_list *t, char *line, int *i, t_command *c)
{
	int			ret;

	if (line[*i] == ' ')
		(*i)++;
	else if (line[*i] == '>' || line[*i] == '<')
	{
		if ((ret = ft_redirections(t, line, i)) != 1)
			return (ret);
	}
	else if (line[*i] == ';' && c->quote == 0)
	{
		(*i)++;
		return (1);
	}
	return (3);
}

int		ft_parser_arg(t_list **t, char *line, int *i, t_command **c)
{
	int			ret;

	if (line[*i] == '|')
	{
		if (!(ft_add_list(*t)))
			return (0);
		*t = (*t)->next;
		(*c)->k = -1;
		(*i)++;
	}
	else
	{
		*c = (*t)->content;
		if ((ret = ft_arg(*c, line, i, &((*c)->k))) != 1)
			return (ret);
	}
	return (3);
}

int		ft_parser(t_list *t, char *line, int *i)
{
	int			ret;
	t_command	*c;

	c = t->content;
	while (line[*i])
	{
		if (line[*i] == ' ' || line[*i] == '>' || line[*i] == '<'
		|| (line[*i] == ';' && c->quote == 0))
		{
			if ((ret = ft_parser_symbol(t, line, i, c)) != 3)
				return (ret);
		}
		else
		{
			if ((ret = ft_parser_arg(&t, line, i, &c)) != 3)
				return (ret);
		}
	}
	if (c->quote != 0)
		ft_putstr_fd("WARNING : Quotes automatically closed\n", 2);
	if (ft_strlen(c->arg[0]) == 0)
		return (2);
	return (1);
}

int		ft_arg(t_command *c, char *line, int *i, int *k)
{
	int			ret;

	(*k)++;
	if (*k != 0)
	{
		if (!(c->arg = ft_realloc_arg(c->arg)))
			return (0);
	}
	if (!(ret = ft_new_arg(c, line, i, k)))
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
