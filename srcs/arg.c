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
        
        if (line[*i] == '$' && c->quote != 1)
        {
            c->env = 1;
            (*i)++;
        }
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
/*
char    *ft_var_exist(char *arg, char ***env)
{
    int j = 0;
    
    while (*env && (*env)[j])
    {
        if ((*env)[j] && ft_strncmp((*env)[j], arg, ft_strlen(arg)) == 0)
        {
            return (j);
        }
        j++;
    }
    return (-1);
}*/
char    *ft_env_var(char *arg, char ***env)
{
    int j = 0;
    char    *new_arg;

    while (*env && (*env)[j])
    {
        if ((*env)[j] && ft_strncmp((*env)[j], arg, ft_strlen(arg)) == 0)
        {
            new_arg = ft_substr((*env)[j], ft_strlen(arg) + 1, ft_strlen((*env)[j]) - ft_strlen(arg) + 1);
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
