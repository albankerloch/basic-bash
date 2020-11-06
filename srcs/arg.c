/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 22:43:15 by aduchemi          #+#    #+#             */
/*   Updated: 2020/11/05 22:43:17 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_quotes(char *line, int *i, int *quote, int *ret)
{
    ft_skip_quotes(line, i, quote);
    if (*quote == 0 && (line[*i] == ' ' || line[*i] == '>' || line[*i] == '<' || line[*i] == '|' || line[*i] == ';'))
        return (0);
    *ret = ft_backslash(line, i, quote);
    if (!(line[*i]))
        return (0);
    return (1);
}

int     ft_redir_var(int quote, char *line, int *i, char **arg)
{
    int i_start;
    int ret;

    if (line[*i] == '$' && quote != 1 && line[*i + 1] && (ft_isalnum(line[*i + 1]) || line[*i + 1] == '_'))
    {
        i_start = *i;
        (*i)++;
        if(!(ret = ft_realloc_var(arg, line, i, &fix)))
            return (0);
        if (ret == 2)
            return (ft_ambiguous_redir(line, i_start, i, &fix));
    }
    return (1);
}

int    ft_new_input(t_command *c, char *line, int *i)
{
    int ret;
    int i_start;

    while (line[*i])
    {
        if (!ft_quotes(line, i, &(c->quote), &ret))
            break;
        if (ret == 0 && line[*i] == '$' && c->quote != 1 && line[*i + 1] && (ft_isalnum(line[*i + 1]) || line[*i + 1] == '_'))
        {
            if ((ret = ft_redir_var(c->quote, line, i, &(c->n_input))) != 1)
                return (ret);
        }
        else if (ret == 0 && line[*i] == '$' && c->quote != 1 && line[*i + 1] && line[*i + 1] == '?')
        {
            (*i)++;
            if(!(ft_realloc_fix_error(&(c->n_input), &fix)))
                return (0);
        }
        else if (!(c->n_input = ft_realloc_concat(c->n_input, line[*i])))
            return (0);
        (*i)++;
        ft_close_quotes(line, i, &(c->quote));
    }
    return (1);
}

int    ft_new_out(t_command *c, char *line, int *i)
{
    int ret;
    int i_start;

    while (line[*i])
    {
        if (!ft_quotes(line, i, &(c->quote), &ret))
            break;
        if (ret == 0 && line[*i] == '$' && c->quote != 1 && line[*i + 1] && (ft_isalnum(line[*i + 1]) || line[*i + 1] == '_'))
        {
            if ((ret = ft_redir_var(c->quote, line, i, &(c->n_out))) != 1)
                return (ret);
        }
        else if (ret == 0 && line[*i] == '$' && c->quote != 1 && line[*i + 1] && line[*i + 1] == '?')
        {
            (*i)++;
            if(!(ft_realloc_fix_error(&(c->n_out), &fix)))
                return (0);
        }
        else if (!(c->n_out = ft_realloc_concat(c->n_out, line[*i])))
            return (0);
        (*i)++;
        ft_close_quotes(line, i, &(c->quote));
    }
    return (1);
}

int    ft_new_arg(t_command *c, char *line, int *i, int *k)
{
    int var;
    int ret;

    ret = 1;
    while (line[*i])
    {
        if (!ft_quotes(line, i, &(c->quote), &var))
            break;
        if (var == 0 && line[*i] == '$' && c->quote != 1 && line[*i + 1] && (ft_isalnum(line[*i + 1]) || line[*i + 1] == '_'))
        {
            (*i)++;
            if(!(ret = ft_realloc_var(&(c->arg[*k]), line, i, &fix)))
                    return (0);
            else if (ret == 2)
                ft_close_quotes(line, i, &(c->quote));
        }
        else if (var == 0 && line[*i] == '$' && c->quote != 1 && line[*i + 1] && line[*i + 1] == '?')
        {
            (*i)++;
            if(!(ft_realloc_fix_error(&(c->arg[*k]), &fix)))
                return (0);
        }
        else if (!(c->arg[*k] = ft_realloc_concat(c->arg[*k], line[*i])))
            return (0);
        (*i)++;
        ft_close_quotes(line, i, &(c->quote));
    }
    return (ret);
}