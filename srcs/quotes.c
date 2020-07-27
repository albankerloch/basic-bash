#include "../includes/minishell.h"

int    ft_backslash(t_command *c, char *line, int *i)
{
    if (line[*i] == '\\' && c->quote == 0)
        *i = *i + 1;
    else if (line[*i] == '\\' && c->quote == 2 && line[*i + 1] && (line[*i + 1] == '`' || line[*i + 1] == '\"'))
        *i = *i + 1;
    return (0);
}

void    ft_skip_quotes(t_command *c, char *line, int *i)
{
    while ((line[*i] == '\'' && c->quote != 2) || (line[*i] == '\"' && c->quote != 1))
    {
        if (c->quote == 0 && line[*i] == '\'')
            c->quote = 1;
        else if (c->quote == 0 && line[*i] == '\"')
            c->quote = 2;
        else
            c->quote = 0;
        (*i)++;
    }
}