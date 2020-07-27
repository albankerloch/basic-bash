/*best parser ever*/

#include "../includes/minishell.h"

void    ft_command_construct(t_command *c)
{
    c->input = 0;
    c->n_input = malloc(1);
    c->add = 0;
    c->quote = 0;
    c->out = 1;
    c->n_out = malloc(1);
    c->err = 2;
    c->n_err = malloc(1);
    c->arg = malloc(sizeof(char*));
    c->arg[0] = malloc(1);
}

t_command ft_parser(char *line)
{
    t_command   c;
    int         i;
    int         t;

    t = -1;
    i = 0;
    ft_command_construct(&c);
    while(line[i])
    {
        /* if (line[i] == quote)
            vérif finie ---> erreur
            verif faux arg (double quote d'affilé) --> avance 2
            else
            t++ et realloc arg
            if (line[i] == quote)
                c.quote = 1 (ou c.quote= 2) et avance de 1
            boucle (avec à l'intérieur gestion des backslah)
        */
        if (line[i] == ' ')
            i++;
        else
        {
            if (ft_check_end_quote(&c, line, i))
                return (c);
            t++;
            if (t != 0)
                c.arg = ft_realloc_arg(c.arg);
            while (line[i])
            {
                //  printf("line[%d]=%c quote=%d t=%d\n", i, line[i], c.quote, t);
                while (line[i] && (line[i] == '\"' || line[i] == '\''))
                {
                    if (c.quote == 2 && line[i] == '\"')
                        c.quote = 0;
                    else if (c.quote == 1 && line[i] == '\'')
                        c.quote = 0;
                    else if (c.quote == 0 && line[i] == '\"')
                        c.quote = 2;
                    else if (c.quote == 0 && line[i] == '\'')
                        c.quote = 1;
                    else
                        break ;
                    i++;
                }
                if (ft_backslash(&c, line, &i))
                {
                    printf("erreur à gérer\n");
                    c.arg = NULL;
                    return (c);
                }
                if (c.quote == 0 && line[i] == ' ' && line[i - 1] != '\\')
                    break ;
                if (!ft_redirection(&c, line, &i))
                    c.arg[t] = ft_realloc_concat(c.arg[t], line[i]);
                else
                    printf("redir\n");
                i++;
            }
        }
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