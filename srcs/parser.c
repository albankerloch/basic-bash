#include "../includes/minishell.h"

int ft_parser(t_list *t, char *line, t_fix *fix, int *i)
{
    int         k;
    int         ret;
    t_command   *c;

    k = -1;
    while(line[*i])
    {
        if (line[*i] == ' ')
            (*i)++;
        else if (line[*i] == '>')
        {
            if ((ret = ft_redirection_right(t->content, line, i, fix)) != 1)
                return (ret);
        }
        else if (line[*i] == ';' && c->quote == 0)
        {
            (*i)++;
            return (1);
        }
        else if (line[*i] == '<')
        {
            if ((ret = ft_redirection_left(t->content, line, i, fix)) != 1)
                return (ret);
        }
        else if (line[*i] == '|')
        {
            if(!(ft_add_list(t, fix)))
                return (0);
            t = t->next;
            k = -1;
            (*i)++;
        }
        else
        {
            c = t->content;
            k++;
            if (k != 0)
            {
           //     printf("k=%d\n", k);
                if (!(c->arg = ft_realloc_arg(c->arg)))
                    return (0);
             //   printf("realloc arg=%s len=%zu\n", c->arg[k], ft_strlen(c->arg[k]));
            }
            if (!(ft_new_arg(c, line, i, fix)))
                return (0);
     //       if (k > 0)
       //         printf("len=%zu arg=%s -%c-\n", ft_strlen(c->arg[1]), c->arg[1], line[*i]);
        }
    }
    if (c->quote != 0)
        ft_putstr_fd("WARNING : Quotes automatically closed\n", 2);
    return (1);
}