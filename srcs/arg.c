#include "../includes/minishell.h"

int    ft_new_arg(char **arg, t_command *c, char *line, int *i)
{
    while (line[*i])
    {
     //   printf("line[%d]=%c quote=%d k=%d\n", *i, line[*i], c->quote, *k);
        ft_skip_quotes(line, i, &(c->quote));
        ft_backslash(line, i, &(c->quote));
        if(!(*arg = ft_realloc_concat(*arg, line[*i])))
            return (0);
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
    return (1);
}

int    ft_arg_var(char **arg, t_fix *fix)
{
    int j;
    char *new_arg;

    new_arg = NULL;
    j = 0;
    while ((*arg)[j])
    {
        if ((*arg)[j] == '$' && (*arg)[j + 1])
        {
            j++;
            if (!(new_arg = ft_env_var(*arg, j, fix)))
                return (0);
            if (!(*arg = ft_strjoin(ft_substr(*arg, 0, j - 1), new_arg)))
            {
                free(new_arg);
                return (0);
            }
            free(new_arg);
        }
        j++;
    }
    return (1);
}

char   *ft_env_var(char *arg, int h, t_fix *fix)
{
    char    *nom_var;
    char    *val_var;
    int j;
    int i;
    
    j = h;
    while (arg[j] && arg[j] != '$' && arg[j] != '=')
        j++;
    if (!(nom_var = ft_substr(arg, h, j - h)))
        return (NULL);
    if (!(ft_valeur_variable(fix, &nom_var, &val_var)))
        return (NULL);
    if (val_var != NULL && j != ft_strlen(arg))
        return(ft_join_end_var(&val_var, arg, j));
    return (val_var);
}

char    *ft_realloc_substr(t_fix *fix, char **nom_var, char **val_var, int i)
{
    char *temp;

    if(!(temp = ft_substr(fix->env[i], ft_strlen(*nom_var) + 1, ft_strlen(fix->env[i]) - ft_strlen(*nom_var) + 1)))
        return (NULL);
    free(val_var);
    return (temp);
}

int    ft_valeur_variable(t_fix *fix, char **nom_var, char **val_var)
{
    int i;

    if(!(*val_var = malloc(sizeof(char))))
        return (0);
    (*val_var)[0] = '\0';
    i = 0;
    while (fix->env && fix->env[i])
    {
        if (fix->env[i] && ft_strncmp(fix->env[i], *nom_var, ft_strlen(*nom_var)) == 0 && fix->env[i][ft_strlen(*nom_var)] == '=')
            if(!(*val_var = ft_realloc_substr(fix, nom_var, val_var, i)))
                return (1);
        i++;
    }
    free(*nom_var);
    return (1);
}

char    *ft_join_end_var(char **val_var, char *arg, int j)
{
    char    *val_var2;

    if (!(val_var2 = malloc(sizeof(char))))
        return (NULL);
    val_var2[0] = '\0';
    val_var2 = ft_strjoin(*val_var, ft_substr(arg, j, ft_strlen(arg) - j));
    free(*val_var);
    return (val_var2);
}