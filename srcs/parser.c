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
    t_command *c;

    k = -1;
    i = 0;
    while(line[i])
    {
        if (line[i] == ' ')
            i++;
            // si on est au début d'une redirection
        else if (line[i] == '>')
            ft_redirection_right(t->content, line, &i, &k);
        else if (line[i] == '<')
        {
            if (ft_redirection_left(t->content, line, &i, &k))
                return (1);
        }
        else if (line[i] == '|')
        {
            ft_lstadd_back(&t, ft_lstnew(ft_command_construct()));
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
                c->arg = ft_realloc_arg(c->arg);
            ft_name(&(c->arg[k]), c, line, &i);
            ft_arg_var(&(c->arg[k]), fix);
        }
    }
    if (c->quote != 0)
    {
        ft_putstr("WARNING : Quotes automatically closed");
        ft_putchar('\n');
    }
    return (0);
}