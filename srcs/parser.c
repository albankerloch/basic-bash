/*best parser ever*/

/* while(line[i] != '\0')
    {
        //realloc char si diff " ' > space et pas debut d'un redic en debut mot
        // si space realloc une fois (cmp avec malloc en cours arg)
        // si " ', cherche second, realloc ou erreur
        // si redir, chg struct
        
    i++;
    }
*/

#include "../includes/minishell.h"

int ft_parser(t_command *c, char *line)
{
    int         i;
    int         t;

    t = -1;
    i = 0;
    while(line[i])
    {
        if (line[i] == ' ')
            i++;
            // si on est au début d'une redirection
        else if (line[i] == '>')
            ft_redirection_right(c, line, &i);
        else if (line[i] == '<')
        {
            if (ft_redirection_left(c, line, &i))
                return (1);
        }
        else
        {
            // sinon on est au début d'un nouvel argument => ajout d'un char* à c.arg
            t++;
            if (t != 0)
            c->arg = ft_realloc_arg(c->arg);
            while (line[i])
            {
                //   printf("line[%d]=%c quote=%d t=%d\n", i, line[i], c->quote, t);
                ft_skip_quotes(line, &i, &(c->quote));
                ft_backslash(line, &i, &(c->quote));
                c->arg[t] = ft_realloc_concat(c->arg[t], line[i]);
                i++;
                if ((line[i] == '\"' && c->quote == 2) || (line[i] == '\'' && c->quote == 1))
                {
                    c->quote = 0;
                    i++;
                }
                if (c->quote == 0 && (line[i] == ' ' || line[i] == '>' || line[i] == '<'))
                    break;
                //printf("fin boucle line[%d]=%c quote=%d t=%d\n", i, line[i], c.quote, t);
            }
        }
    }
    if (c->quote != 0)
    {
        ft_putstr("WARNING : Quotes automatically closed");
        ft_putchar('\n');
    }
    printf("output stdout = %s \n", c->n_out);
    printf("redir = %d \n", c->add);
    printf("input stdin = %s \n", c->n_input);
    printf("flag input = %d \n", c->input);
    return (0);
}