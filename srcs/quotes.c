#include "../includes/minishell.h"

void    ft_skip_quotes(char *line, int *i, int *quote)
{
    while ((line[*i] == '\'' && *quote != 2) || (line[*i] == '\"' && *quote != 1))
    {
        if (*quote == 0 && line[*i] == '\'')
            *quote = 1;
        else if (*quote == 0 && line[*i] == '\"')
            *quote = 2;
        else
            *quote = 0;
        (*i)++;
    }
}

int    ft_backslash(char *line, int *i, int *quote)
{
    if (line[*i] && line[*i] == '\\' && *quote == 0)
        (*i)++;
    else if (line[*i] && line[*i] == '\\' && *quote == 2 && line[*i + 1] && (line[*i + 1] == '`' || line[*i + 1] == '\"'))
        (*i)++;
    return (0);
}
