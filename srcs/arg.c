#include "../includes/minishell.h"

int    ft_name(char **arg, t_command *c, char *line, int *i)
{
    while (line[*i])
    {
     //   printf("line[%d]=%c quote=%d k=%d\n", *i, line[*i], c->quote, *k);
        ft_skip_quotes(line, i, &(c->quote));
        ft_backslash(line, i, &(c->quote));
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

void    ft_arg_var(char **arg, t_fix *fix)
{
    int j;
    int tmp;
    char    *new_arg;

    new_arg = NULL;
    j = 0;
    while ((*arg)[j])
    {
        if ((*arg)[j] == '$' && (*arg)[j + 1])
        {
            tmp = j;
            j++;
            new_arg = ft_env_var(*arg, &j, fix);
          //  printf("arg=%s new_arg=%s\n\n", *arg, new_arg);
            *arg = ft_strjoin(ft_substr(*arg, 0, tmp), new_arg);
            free(new_arg);
            j = tmp + 1;
        }
        j++;
    }
}

char   *ft_env_var(char *arg, int *h, t_fix *fix)
{
    char    *temp;
    char    *val_var;
    char    *val_var2;
    int j;
    int i;
    
    j = *h;
    while (arg[j] && arg[j] != '$')
        j++;
   // printf("%d h=%d j=%d len=%lu\n", j - h - 1, h, j, ft_strlen(arg));
    temp = ft_substr(arg, *h, j - *h);
    val_var = malloc(sizeof(char));
    val_var[0] = '\0';
    i = 0;
    while (fix->env && fix->env[i])
    {
        if (fix->env[i] && ft_strncmp(fix->env[i], temp, ft_strlen(temp)) == 0 && fix->env[i][ft_strlen(temp)] == '=')
            val_var = ft_substr(fix->env[i], ft_strlen(temp) + 1, ft_strlen(fix->env[i]) - ft_strlen(temp) + 1);
        i++;
    }
    if (val_var != NULL && j != ft_strlen(arg) && arg[j] == '$')
    {
        val_var2 = malloc(sizeof(char));
        val_var2[0] = '\0';
        val_var2 = ft_strjoin(val_var, ft_substr(arg, j, ft_strlen(arg) - j));
        free(temp);
        free(val_var);
        *h = *h + ft_strlen(val_var2) - 1;
        return (val_var2);
    }
    if (val_var)
        *h = *h + ft_strlen(val_var) - 1;
    else
        *h = *h + ft_strlen(temp) - 1;
    free(temp);
    return (val_var);
}