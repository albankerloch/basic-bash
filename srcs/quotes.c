#include "../includes/minishell.h"

int    ft_simple_quoting(t_command *c, char *line, int *i)
{
    if (ft_check_end_quote(c, line, *i, 1))
        return (1);
    if (line[*i - 1] && line[*i - 1] != '\\')
    {
        while (line[*i] == '\'' && c->quote != 2)
        {
            *i = *i + 1;
            if (c->quote == 0 || c->quote == 3)
                c->quote = 1;
            else if (c->quote == 1)
                c->quote = 0;
        }
    }
    return (0);
}

int    ft_double_quoting(t_command *c, char *line, int *i)
{
    if (ft_check_end_quote(c, line, *i, 2))
        return (1);
    if (line[*i - 1] && line[*i - 1] != '\\')
    {
        while (line[*i] == '\"' && c->quote != 1)
        {
            *i = *i + 1;
            if (c->quote == 0 || c->quote == 3)
                c->quote = 2;
            else if (c->quote == 2)
                c->quote = 0;
        }
    }
    return (0);
}

int    ft_backslash(t_command *c, char *line, int *i)
{
    if (line[*i] == '\\' && c->quote == 0)
        *i = *i + 1;
    else if (line[*i] == '\\' && c->quote == 1 && line[*i + 1] && line[*i + 1] == '\'')
        return (1);   
    else if (line[*i] == '\\' && c->quote == 2 && line[*i + 1] && (line[*i + 1] == '`' || line[*i + 1] == '\"'))
        *i = *i + 1;
    return (0);
}

int    ft_check_end_quote(t_command *c, char *line, int i, int q)
{
  //  i++;
  //  printf("check end line[%d]=%c quote=%d\n", i, line[i], c->quote);
    if (c->quote != 0 && c->quote != 3)
        return (0);
    else if (q == 2)
    {
        while (line[i] != '\0')
        {
            if (line[i] == '\"')
                return (0);
            i++;
        }
        c->arg = NULL;
        printf("erreur double quote ouverte i=%d\n", i);
    }
    else if (q == 1)
    {
        while (line[i] != '\0')
        {
            if (line[i] == '\'')
                return (0);
            i++;
        }
        c->arg = NULL;
        printf("erreur simple quote ouverte i=%d\n", i);
    }
    return (1);
}