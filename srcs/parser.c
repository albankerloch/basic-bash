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

int ft_parser(t_list *t, char *line, t_fix *fix)
{
    int         i;
    int         k;
    int         ret;
    t_command *c;

    k = -1;
    i = 0;
    while(line[i])
    {
        if (line[i] == ' ')
            i++;
            // si on est au début d'une redirection
        else if (line[i] == '>')
        {
            if (!(ft_redirection_right(t->content, line, &i, &k)))
                return (0);
        }
        else if (line[i] == '<')
        {
            ret = ft_redirection_left(t->content, line, &i, &k);
            if (ret != 1)
                return (ret);
        }
        else if (line[i] == '|')
        {
            if(!(ft_add_list(t, fix)))
                return (0);
            t = t->next;
            k = -1;
            i++;
        }
        else
        {
            // sinon on est au début d'un nouvel argument => ajout d'un char* à c.arg
            c = t->content;
            k++;
            if (k != 0)
            {
                if (!(c->arg = ft_realloc_arg(c->arg)))
                    return (0);
            }
            if (!(ft_new_arg(&(c->arg[k]), c, line, &i)))
                return (0);
            if (!(ft_arg_var(&(c->arg[k]), fix)))
                return (0);
          //  printf("arg %d = %s\n", k, c->arg[k]);
        }
    }
    if (c->quote != 0)
    {
        ft_putstr("WARNING : Quotes automatically closed");
        ft_putchar('\n');
    }
    return (1);
}