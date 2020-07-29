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

void    ft_command_construct(t_command *c)
{
    c->input = 0;
    c->n_input = malloc(1);
    c->n_input[0] = '\0';
    c->add = 0;
    c->quote = 0;
    c->out = 1;
    c->n_out = malloc(1);
    c->n_out[0] = '\0';
    c->arg = malloc(sizeof(char*));
    c->arg[0] = malloc(1);
    c->arg[0][0] = '\0';
}

void    ft_command_destroy(t_command *c)
{
    int     i;

    i = 0;
    free(c->n_input);
    free(c->n_out);
    while (c->arg[i])
    {
     //   printf("c->arg[%d]=%s\n", i, c->arg[i]);
        free(c->arg[i]);
        c->arg[i] = NULL;
        i++;
    }
    free(c->arg);
    c->arg = NULL;
}

void ft_parser(t_command *c, char *line)
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
            ft_redirection(c, line, &i);
        else
        {
            // sinon on est au début d'un nouvel argument => ajout d'un char* à c.arg
            t++;
            if (t != 0)
            c->arg = ft_realloc_arg(c->arg);
            while (line[i])
            {
                //   printf("line[%d]=%c quote=%d t=%d\n", i, line[i], c->quote, t);
                ft_skip_quotes(c, line, &i);
                ft_backslash(c, line, &i);
                c->arg[t] = ft_realloc_concat(c->arg[t], line[i]);
                i++;
                if ((line[i] == '\"' && c->quote == 2) || (line[i] == '\'' && c->quote == 1))
                {
                    c->quote = 0;
                    i++;
                }
                if (c->quote == 0 && (line[i] == ' ' || line[i] == '>'))
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
}

int    ft_redirection(t_command *c, char *line, int *i)
{
    if (line[*i + 1] && line[*i + 1]== '>')
    {
        *i = *i + 2;
        c->add = 2;
        return (ft_redir_right(c, line, i));
    }
    else
    {
        *i = *i + 1;
        c->add = 1;
        return (ft_redir_right(c, line, i));
    }
    return (0);
}

int    ft_redir_right(t_command *c, char *line, int *i)
{
    //printf("fd output = %c | i = %d | line[i] = '%c' \n", output, *i, line[*i]);
    while (line[*i] == ' ')
        *i = *i + 1;
    if (c->n_out[0] != '\0')
    {
        free(c->n_out);
        c->n_out = malloc(1);
        c->n_out[0] = '\0';
    }
    //printf("--> i = %d | line[i] = '%c' \n", *i, line[*i]);
    while (line[*i] != ' ' && line[*i] != '\0')
    {
        c->n_out = ft_realloc_concat(c->n_out, line[*i]);
        *i = *i + 1;
    }
    ft_touch(c);
    return (1);
}

void    ft_touch(t_command *c)
{
    int fd;

    if (c->add == 1)
        fd = open(c->n_out, O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | \
        S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    else if (c->add == 2)
        fd = open(c->n_out, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | \
        S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    close(fd);
}
