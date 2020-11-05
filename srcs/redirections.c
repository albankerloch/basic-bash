/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 22:43:42 by aduchemi          #+#    #+#             */
/*   Updated: 2020/11/05 22:43:43 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_redirections(t_list *t, char *line, int *i)
{
    int ret;
    
    if (line[*i] == '>')
    {
        if ((ret = ft_redirection_right(t->content, line, i)) != 1)
            return (ret);
    }
    else if (line[*i] == '<')
    {
        if ((ret = ft_redirection_left(t->content, line, i)) != 1)
            return (ret);
    }
    return (1);
}

int    ft_redirection_right(t_command *c, char *line, int *i)
{
    if (line[*i + 1] && line[*i + 1] == '>')
    {
        *i = *i + 2;
        c->add = 2;
        return (ft_redir_right(c, line, i));
    }
    *i = *i + 1;
    c->add = 1;
    return (ft_redir_right(c, line, i));
}

int    ft_redir_right(t_command *c, char *line, int *i)
{
    int ret;

    while (line[*i] == ' ')
        (*i)++;
    if (!line[*i])
        return (ft_syntax_error(&fix, "newline"));
    if (c->n_out[0] != '\0')
    {
        free(c->n_out);
        if (!(c->n_out = malloc(sizeof(char *))))
            return (0);
        c->n_out[0] = '\0';
    }
    if ((ret = ft_new_out(c, line, i, &fix)) != 1)
        return (ret);
    return (ft_touch(c));
}

int    ft_redirection_left(t_command *c, char *line, int *i)
{
    int ret;

    *i = *i + 1;
    c->input = 1;
    while (line[*i] == ' ')
        *i = *i + 1;
    if (!line[*i])
        return (ft_syntax_error(&fix, "newline"));
    if (c->n_input[0] != '\0')
    {
        free(c->n_input);
        if (!(c->n_input = malloc(sizeof(char *))))
            return (0);
        c->n_input[0] = '\0';
    }
    if ((ret = ft_new_input(c, line, i, &fix)) != 1)
        return (ret);
    return (ft_checkfile(c, &fix));
}

int   ft_ambiguous_redir(char *line, int i_start, int *i, t_fix *fix)
{
    ft_putstr_fd("bash: ", 2);
    while (i_start <= *i)
    {
        ft_putchar_fd(line[i_start], 2);
        i_start++;
    }
    while (line[*i])
        (*i)++;
    ft_putstr_fd(" : ambiguous redirect\n", 2);
    fix->error = 1;
    return (2);
}
