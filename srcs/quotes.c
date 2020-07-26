#include "../includes/minishell.h"

int    ft_backslash(t_command *c, char *line, int *i)
{
    if (line[*i] == '\\' && c->quote == 0)
        *i = *i + 1;
    else if (line[*i] == '\\' && c->quote == 2 && line[*i + 1] && (line[*i + 1] == '`' || line[*i + 1] == '\"'))
        *i = *i + 1;
    return (0);
}