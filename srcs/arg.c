#include "../includes/minishell.h"

int    ft_name(t_command *c, char *line, int *i, int *k)
{
    (*k)++;
    if (*k != 0)
        c->arg = ft_realloc_arg(c->arg);
    while (line[*i])
    {
     //   printf("line[%d]=%c quote=%d k=%d\n", *i, line[*i], c->quote, *k);
        ft_skip_quotes(line, i, &(c->quote));
        ft_backslash(line, i, &(c->quote));
        c->arg[*k] = ft_realloc_concat(c->arg[*k], line[*i]);
        (*i)++;
        if ((line[*i] == '\"' && c->quote == 2) || (line[*i] == '\'' && c->quote == 1))
        {
            c->quote = 0;
            (*i)++;
        }
        if (c->quote == 0 && (line[*i] == ' ' || line[*i] == '>' || line[*i] == '<' || line[*i] == '|'))
            break;
       // printf("argk = %s\n", c->arg[*k]);
    }
    return (0);
}