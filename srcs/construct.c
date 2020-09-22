#include "../includes/minishell.h"

t_command *ft_command_construct()
{
    t_command *c;

    c = malloc(sizeof(t_command));
    c->input = 0;
    c->n_input = malloc(1);
    c->n_input[0] = '\0';
    c->add = 0;
    c->quote = 0;
    c->env = 0;
    c->n_out = malloc(1);
    c->n_out[0] = '\0';
    c->arg = malloc(sizeof(char*));
    c->arg[0] = malloc(1);
    c->arg[0][0] = '\0';
    return(c);
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