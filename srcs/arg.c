#include "../includes/minishell.h"

int    ft_new_input(t_command *c, char *line, int *i, t_fix *fix)
{
    int ret;
    int i_start;

    while (line[*i])
    {
        ft_skip_quotes(line, i, &(c->quote));
        ret = ft_backslash(line, i, &(c->quote));
        if (ret == 0 && line[*i] == '$' && c->quote != 1 && line[*i + 1] && (ft_isalnum(line[*i + 1]) || line[*i + 1] == '_'))
        {
            i_start = *i;
            (*i)++;
            if(!(ret = ft_realloc_var(&(c->n_input), line, i, fix)))
                return (0);
            if (ret == 2)
                return (ft_ambiguous_redir(line, i_start, i, fix));
        }
        else if (ret == 0 && line[*i] == '$' && c->quote != 1 && line[*i + 1] && line[*i + 1] == '?')
        {
            (*i)++;
            if(!(ft_realloc_fix_error(&(c->n_input), fix)))
                return (0);
        }
        else
        {
            if(!(c->n_input = ft_realloc_concat(c->n_input, line[*i])))
                return (0);
        }
        (*i)++;
        ft_close_quotes(line, i, &(c->quote));
        if (c->quote == 0 && (line[*i] == ' ' || line[*i] == '>' || line[*i] == '<' || line[*i] == '|' || line[*i] == ';'))
            break;
    }
    return (1);
}

int    ft_new_out(t_command *c, char *line, int *i, t_fix *fix)
{
    int ret;
    int var;
    int i_start;

    ret = 1;
    while (line[*i])
    {
        ft_skip_quotes(line, i, &(c->quote));
        if (c->quote == 0 && (line[*i] == ' ' || line[*i] == '>' || line[*i] == '<' || line[*i] == '|' || line[*i] == ';'))
            break;
        var = ft_backslash(line, i, &(c->quote));
        if (!(line[*i]))
            break;
        if (var == 0 && line[*i] == '$' && c->quote != 1 && line[*i + 1] && (ft_isalnum(line[*i + 1]) || line[*i + 1] == '_'))
        {
            i_start = *i;
            (*i)++;
            if(!(ret = ft_realloc_var(&(c->n_out), line, i, fix)))
                return (0);
            if (ret == 2 && line[*i + 1] == 0)
                return (ft_ambiguous_redir(line, i_start, i, fix));
            else
                ret = 1;            
        }
        else if (var == 0 && line[*i] == '$' && c->quote != 1 && line[*i + 1] && line[*i + 1] == '?')
        {
            (*i)++;
            if(!(ft_realloc_fix_error(&(c->n_out), fix)))
                return (0);
        }
        else
        {
  //          if (ret == 1 && c->quote == 0)
    //            c->quote = 1;
       //     printf("realloc concat line=%c\n", line[*i]);
            if(!(c->n_out = ft_realloc_concat(c->n_out, line[*i])))
                return (0);
        }
        (*i)++;
        ft_close_quotes(line, i, &(c->quote));
    }
 //   if (c->n_out[0] == '$' && c->quote == 1)
   //     c->quote = 0;
    return (ret);
}

int    ft_new_arg(t_command *c, char *line, int *i, t_fix *fix)
{
    int k;
    int var;
    int ret;

    k = 0;
    while(c->arg[k])
        k++;
    k--;
    ret = 1;
    while (line[*i])
    {
        ft_skip_quotes(line, i, &(c->quote));   
        if (c->quote == 0 && (line[*i] == ' ' || line[*i] == '>' || line[*i] == '<' || line[*i] == '|' || line[*i] == ';'))
            break;
        var = ft_backslash(line, i, &(c->quote));
        if (!(line[*i]))
            break;
        if (var == 0 && line[*i] == '$' && c->quote != 1 && line[*i + 1] && (ft_isalnum(line[*i + 1]) || line[*i + 1] == '_'))
        {
            (*i)++;
            if(!(ret = ft_realloc_var(&(c->arg[k]), line, i, fix)))
                    return (0);
            else if (ret == 2)
                ft_close_quotes(line, i, &(c->quote));
        }
        else if (var == 0 && line[*i] == '$' && c->quote != 1 && line[*i + 1] && line[*i + 1] == '?')
        {
            (*i)++;
            if(!(ft_realloc_fix_error(&(c->arg[k]), fix)))
                return (0);
        }
        else
        {
            if(!(c->arg[k] = ft_realloc_concat(c->arg[k], line[*i])))
                return (0);
        }
        (*i)++;
        ft_close_quotes(line, i, &(c->quote));
    }
    return (ret);
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