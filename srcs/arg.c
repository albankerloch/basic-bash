/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 22:43:15 by aduchemi          #+#    #+#             */
/*   Updated: 2020/11/06 21:28:31 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_quotes(char *line, int *i, int *quote, int *ret)
{
	ft_skip_quotes(line, i, quote);
	if (*quote == 0 && (line[*i] == ' ' || line[*i] == '>' ||
	line[*i] == '<' || line[*i] == '|' || line[*i] == ';'))
		return (0);
	*ret = ft_backslash(line, i, quote);
	if (!(line[*i]))
		return (0);
	return (1);
}

int		ft_redir_var(int quote, char *line, int *i, char **arg)
{
	int		i_start;
	int		ret;

	if (line[*i] == '$' && quote != 1 && line[*i + 1] &&
	(ft_isalnum(line[*i + 1]) || line[*i + 1] == '_'))
	{
		i_start = *i;
		(*i)++;
		if (!(ret = ft_realloc_var(arg, line, i)))
			return (0);
		if (ret == 2)
			return (ft_ambiguous_redir(line, i_start, i));
	}
	return (1);
}

int		ft_new_in_out(t_command *c, char **arg, char *line, int *i)
{
	int		ret;

	while (line[*i])
	{
		if (!ft_quotes(line, i, &(c->quote), &ret))
			break ;
		if (ret == 0 && line[*i] == '$' && c->quote != 1 && line[*i + 1] &&
		(ft_isalnum(line[*i + 1]) || line[*i + 1] == '_'))
		{
			if ((ret = ft_redir_var(c->quote, line, i, arg)) != 1)
				return (ret);
		}
		else if (ret == 0 && line[*i] == '$' && c->quote != 1 &&
		line[*i + 1] && line[*i + 1] == '?')
		{
			if (!(ft_realloc_g_f_error(arg, i)))
				return (0);
		}
		else if (!(*arg = ft_realloc_concat(*arg, line[*i])))
			return (0);
		(*i)++;
		ft_close_quotes(line, i, &(c->quote));
	}
	return (1);
}

int		ft_new_arg_var(char **arg, char *line, int *i, int *quote)
{
	int		ret;

	ret = 1;
	(*i)++;
	if (!(ret = ft_realloc_var(arg, line, i)))
		return (0);
	else if (ret == 2)
		ft_close_quotes(line, i, quote);
	return (ret);
}

int		ft_new_arg(t_command *c, char *line, int *i, int *k)
{
	int		var;
	int		ret;

	ret = 1;
	while (line[*i])
	{
		if (!ft_quotes(line, i, &(c->quote), &var))
			break ;
		if (var == 0 && line[*i] == '$' && c->quote != 1 && line[*i + 1] &&
		(ft_isalnum(line[*i + 1]) || line[*i + 1] == '_'))
			ret = ft_new_arg_var(&(c->arg[*k]), line, i, &(c->quote));
		else if (var == 0 && line[*i] == '$' && c->quote != 1 &&
		line[*i + 1] && line[*i + 1] == '?')
			ret = ft_realloc_g_f_error(&(c->arg[*k]), i);
		else if (!(c->arg[*k] = ft_realloc_concat(c->arg[*k], line[*i])))
			return (0);
		if (!ret)
			return (0);
		(*i)++;
		ft_close_quotes(line, i, &(c->quote));
	}
	return (ret);
}
