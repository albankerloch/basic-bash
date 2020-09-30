#include "../includes/minishell.h"

int    ft_name(char **arg, t_command *c, char *line, int *i)
{
    while (line[*i])
    {
     //   printf("line[%d]=%c quote=%d k=%d\n", *i, line[*i], c->quote, *k);
        ft_skip_quotes(line, i, &(c->quote));
        ft_backslash(line, i, &(c->quote));
        
        if (line[*i] == '$' && c->quote != 1)
        {
            c->env = 1;
            (*i)++;
        }
        *arg = ft_realloc_concat(*arg, line[*i]);
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

char    *ft_env_var(char *arg, t_fix *fix)
{
    int j = 0;
    char    *new_arg;

    while (fix->env && fix->env[j])
    {
        if (fix->env[j] && ft_strncmp(fix->env[j], arg, ft_strlen(arg)) == 0 && fix->env[j][ft_strlen(arg)] == '=')
        {
            new_arg = ft_substr(fix->env[j], ft_strlen(arg) + 1, ft_strlen(fix->env[j]) - ft_strlen(arg) + 1);
            free(arg);
            return (new_arg);
        }
        j++;
    }
    new_arg = malloc(1);
    new_arg[0] = '\0';
    free(arg);
    return (new_arg);
}
