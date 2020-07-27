#include "../includes/minishell.h"

int    ft_backslash(t_command *c, char *line, int *i)
{
    if (line[*i] == '\\' && c->quote == 0)
        *i = *i + 1;
    else if (line[*i] == '\\' && c->quote == 2 && line[*i + 1] && (line[*i + 1] == '`' || line[*i + 1] == '\"'))
        *i = *i + 1;
    return (0);
}

<<<<<<< HEAD
int    ft_check_end_quote(t_command *c, char *line, int i)
{
    if (line[i] == '\"' && c->quote != 2)
    {
        i++;
        while (line[i] != '\0')
        {
            if (line[i] == '\"' && line[i - 1] && line[i - 1] != '\\')
                return (0);
            i++;
        }
        c->arg = NULL;
        printf("erreur double quote ouverte i=%d\n", i);
        return (1);
    }
    else if (line[i] == '\'' && c->quote != 1)
    {
        i++;
        while (line[i] != '\0')
        {
            if (line[i] == '\'' && line[i - 1] && line[i - 1] != '\\')
                return (0);
            i++;
        }
        c->arg = NULL;
        printf("erreur simple quote ouverte i=%d\n", i);
        return (1);
    }
    return (0);
=======
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
>>>>>>> origin/quotes_v_alban
}