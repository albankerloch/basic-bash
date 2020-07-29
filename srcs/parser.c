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

int ft_parser(t_list *t, char *line)
{
    int         i;
    int         k;

    k = -1;
    i = 0;
    while(line[i])
    {
        if (line[i] == ' ')
            i++;
            // si on est au début d'une redirection
        else if (line[i] == '>')
            ft_redirection_right(t->content, line, &i);
        else if (line[i] == '<')
        {
            if (ft_redirection_left(t->content, line, &i))
                return (1);
        }
       /* else if (line[i] == '|')
        {
            ft_lstnew()
        }*/
        else
        {
            // sinon on est au début d'un nouvel argument => ajout d'un char* à c.arg
           ft_name(t->content, line, &i, &k);
         /*   k++;
            if (k != 0)
                t->content->arg = ft_realloc_arg(t->content->arg);
            while (line[i])
            {
                //   printf("line[%d]=%c quote=%d t=%d\n", i, line[i], c->quote, t);
                ft_skip_quotes(line, &i, &(t->content->quote));
                ft_backslash(line, &i, &(t->content->quote));
                t->content->arg[t] = ft_realloc_concat(t->content->arg[t], line[i]);
                i++;
                if ((line[i] == '\"' && t->content->quote == 2) || (line[i] == '\'' && t->content->quote == 1))
                {
                    t->content->quote = 0;
                    i++;
                }
                if (t->content->quote == 0 && (line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|'))
                    break;
                //printf("fin boucle line[%d]=%c quote=%d t=%d\n", i, line[i], c.quote, t);
            }*/
        }
    }
  /*  if (t->content->quote != 0)
    {
        ft_putstr("WARNING : Quotes automatically closed");
        ft_putchar('\n');
    }*/
 /*   printf("output stdout = %s \n", t->content->n_out);
    printf("redir = %d \n", t->content->add);
    printf("input stdin = %s \n", t->content->n_input);
    printf("flag input = %d \n", t->content->input);*/
    return (0);
}