#include "../includes/minishell.h"

int    ft_name(char **arg, t_command *c, char *line, int *i)
{
    while (line[*i])
    {
     //   printf("line[%d]=%c quote=%d k=%d\n", *i, line[*i], c->quote, *k);
        ft_skip_quotes(line, i, &(c->quote));
        ft_backslash(line, i, &(c->quote));
        
     /*   if (line[*i] == '$' && line[*i + 1] != '?' && c->quote != 1)
        {
            c->env = 1;
           // (*i)++;
        }*/
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

char    *ft_env_var(char **arg, int i, t_fix *fix)
{
    int j = 0;
    char    *new_arg;
    char    *temp;

   // printf("ENV VAR arg 0 =%s\n", arg[0]);
    temp = ft_substr(arg[i], 1, ft_strlen(arg[i]));
 //   printf("temp =%s\n", temp);
    while (fix->env && fix->env[j])
    {
     //   printf("%s ret strncmp=%d car=%c\n", fix->env[j], ft_strncmp(fix->env[j], temp, ft_strlen(temp)), fix->env[j][ft_strlen(temp)]);
        if (fix->env[j] && ft_strncmp(fix->env[j], temp, ft_strlen(temp)) == 0 && fix->env[j][ft_strlen(temp)] == '=')
        {
            new_arg = ft_substr(fix->env[j], ft_strlen(temp) + 1, ft_strlen(fix->env[j]) - ft_strlen(temp) + 1);
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
