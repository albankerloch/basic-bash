#include "../includes/minishell.h"

int    ft_redirection_right(t_command *c, char *line, int *i, t_fix *fix)
{
    if (line[*i + 1] && line[*i + 1] == '>')
    {
        *i = *i + 2;
        c->add = 2;
        return (ft_redir_right(c, line, i, fix));
    }
    *i = *i + 1;
    c->add = 1;
    return (ft_redir_right(c, line, i, fix));
}

int    ft_redir_right(t_command *c, char *line, int *i, t_fix *fix)
{
    while (line[*i] == ' ')
        (*i)++;
    if (!line[*i])
    {
        ft_putstr_fd("bash: erreur de syntaxe près du symbole inattendu \" newline \"\n", 2);
        return (-1);
    }
    if (c->n_out[0] != '\0')
    {
        free(c->n_out);
        if (!(c->n_out = malloc(sizeof(int))))
            return (0);
        c->n_out[0] = '\0';
    }
    if (!(ft_new_out(c, line, i, fix)))
        return (0);
    return (ft_touch(c));
}

int    ft_redirection_left(t_command *c, char *line, int *i, t_fix *fix)
{
    *i = *i + 1;
    c->input = 1;
    while (line[*i] == ' ')
        *i = *i + 1;
    if (c->n_input[0] != '\0')
    {
        free(c->n_input);
        if (!(c->n_input = malloc(sizeof(int))))
            return (0);
        c->n_input[0] = '\0';
    }
    if (!(ft_new_input(c, line, i, fix)))
        return (0);
    return (ft_checkfile(c));
}