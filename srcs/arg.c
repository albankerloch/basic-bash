#include "../includes/minishell.h"

int    ft_new_arg(char **arg, t_command *c, char *line, int *i)
{
    while (line[*i])
    {
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
        if (c->quote == 0 && (line[*i] == ' ' || line[*i] == '>' || line[*i] == '<' || line[*i] == '|' || line[*i] == ';'))
            break;
    }
    return (1);
}

char *ft_substr_strjoin(char const *s, unsigned int start, size_t len, char const *s2)
{
    char *temp;
    char *new;

    if (!(temp = ft_substr(s, start, len)))
        return (NULL);
    if (!(new = ft_strjoin(temp, s2)))
    {
        free(temp);
        return (NULL);
    }
    free(temp);
    return (new);
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
            if ((*arg)[j] == '?')
                return (1);
            if (!(new_arg = ft_env_var(*arg, j, fix)))
                return (0);
            if (!(*arg = ft_substr_strjoin(*arg, 0, j - 1, new_arg)))
            {
                free(new_arg);
                return (0);
            }
            free(new_arg);
        }
        else
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
    if (!(val_var = ft_valeur_variable(fix, nom_var)))
    {
        free(nom_var);
        return (NULL);
    }
    free(nom_var);
    if (val_var == NULL || j == ft_strlen(arg))
        return(val_var);
    return (ft_join_end_var(val_var, arg, j));
}

char    *ft_valeur_variable(t_fix *fix, char *nom_var)
{
    char    *val_var;
    int i;

    i = 0;
    while (fix->env && fix->env[i])
    {
        if (fix->env[i] && ft_strncmp(fix->env[i], nom_var, ft_strlen(nom_var)) == 0 && fix->env[i][ft_strlen(nom_var)] == '=')
            return (ft_substr(fix->env[i], ft_strlen(nom_var) + 1, ft_strlen(fix->env[i]) - ft_strlen(nom_var) + 1));
        i++;
    }
    if(!(val_var = malloc(sizeof(char))))
        return (NULL);
    val_var[0] = '\0';
    return (val_var);
}

char *ft_strjoin_substr(char const *s1, char const *s, unsigned int start, size_t len)
{
    char *temp;
    char *new;

    if (!(temp = ft_substr(s, start, len)))
        return (NULL);
    if (!(new = ft_strjoin(s1, temp)))
    {
        free(temp);
        return (NULL);
    }
    free(temp);
    return (new);
}

char    *ft_join_end_var(char *val_var, char *arg, int j)
{
    char    *new;

    if (!(new = ft_strjoin_substr(val_var, arg, j, ft_strlen(arg) - j)))
    {
        free(val_var);
        return (NULL);
    }
    free(val_var);
    return (new);
}