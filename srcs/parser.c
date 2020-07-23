/*best parser ever*/

#include "../includes/minishell.h"

void    ft_command_construct(t_command *c)
{
    c->arg = malloc(1);
    c->input = 0;
    c->n_input = malloc(1);
    c->add = 0;
    c->quote = 0;
    c->out = 1;
    c->n_out = malloc(1);
    c->err = 2;
    c->n_err = malloc(1);
}

t_command ft_parser(char *line)
{
    t_command   c;
    int         i;

    i = 0;
    ft_command_construct(&c);
    while(line[i])
    {
        printf("quote=%d line[%d]=%c\n", c.quote, i, line[i]);
        if (line[i] == '\"')
            ft_double_quoting(&c, line, &i);
        else if (line[i] == '\'')
            ft_simple_quoting(&c, line, &i);
        if (ft_backslash(&c, line, &i))
        {
            c.arg = NULL;
            return (c);
        }
        if (!ft_redirection(&c, line, &i))
        {
    	    c.arg = ft_realloc_concat(c.arg, line[i]);
      //      printf("redir ok %d %c %d %s\n", i, line[i], c.quote, c.arg);
        }
       // printf("realloc=%s\n", c.arg);
 //       else   
 //           printf("redir : %d\n", i);
       // if (!(line[i] == '\"' && line[i - 1] && line[i - 1] == '\"'))
        i++;
	}
 
   /* while(line[i] != '\0')
    {
    	//realloc char si diff " ' > space et pas debut d'un redic en debut mot
	// si space realloc une fois (cmp avec malloc en cours arg)
	// si " ', cherche second, realloc ou erreur
	// si redir, chg struct
	
	i++;
	}*/
	// supprimer space a la fin de arg
    return (c);
}

void    ft_simple_quoting(t_command *c, char *line, int *i)
{
    if (line[*i - 1] && line[*i - 1] != '\\')
    {
        while (line[*i] == '\'' && c->quote != 2)
        {
            *i = *i + 1;
            if (c->quote == 0)
                c->quote = 1;
            else if (c->quote == 1)
                c->quote = 0;
        }
    }
}

void    ft_double_quoting(t_command *c, char *line, int *i)
{
    if (line[*i - 1] && line[*i - 1] != '\\')
    {
        while (line[*i] == '\"' && c->quote != 1)
        {
            *i = *i + 1;
            if (c->quote == 0)
                c->quote = 2;
            else if (c->quote == 2)
                c->quote = 0;
        }
    }
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

int    ft_redirection(t_command *c, char *line, int *i)
{
    if ((line[*i] == '1' || line[*i] == '2') && *i > 0 && line[*i - 1] == ' ')
    {
        if (line[*i + 1]== '>')
        {
            if (line[*i + 2] && line[*i + 2] == '>')
            {
                *i = *i + 3;
                 return (ft_add(c, line, i, line[*i - 3]));
            }
            else
            {
                *i = *i + 2;
                return (ft_redir_right(c, line, i, line[*i - 2]));
            }
        }
    }
    else if (line[*i] == '>')
    {
        if (line[*i + 1] && line[*i + 1] == '>')
        {
            *i = *i + 2;
            return (ft_add(c, line, i, 1));
        }
        else
        {
            *i = *i + 1;
            return (ft_redir_right(c, line, i, 1));
        }
    }
    return (0);
}

int    ft_add(t_command *c, char *line, int *i, char output)
{   
    c->add = 1;
   while (line[*i] == ' ')
        *i = *i + 1;
    while (line[*i] != ' ' && line[*i] != '\0')
    {
        if (output == '1')
            c->n_out = ft_realloc_concat(c->n_out, line[*i]);
        else
            c->n_err = ft_realloc_concat(c->n_err, line[*i]);
        *i = *i + 1;
    }
    return (1);
}

int    ft_redir_right(t_command *c, char *line, int *i, char output)
{
    while (line[*i] == ' ')
        *i = *i + 1;
    while (line[*i] != ' ' && line[*i] != '\0')
    {
        if (output == '1')
            c->n_out = ft_realloc_concat(c->n_out, line[*i]);
        else
            c->n_err = ft_realloc_concat(c->n_err, line[*i]);
        *i = *i + 1;
    }
    return (1);
}