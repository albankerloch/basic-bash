#include "../includes/minishell.h"

t_command  *ft_free_part_command(t_command *c, int i)
{    
    if (i >= 1)
        free(c->n_input);
    if (i >= 2)
        free(c->n_out);
    if (i >= 3)
        free(c->arg);
    if (i >= 4)
        free(c->arg[0]);
	free(c);
    return (NULL);
}

void    ft_free_command(t_command *c)
{
    int i;

    free(c->n_out);
	free(c->n_input);
    i = 0;
    while (c->arg[i])
    {
    	free(c->arg[i]);
        i++;
    }
	free(c->arg);
	free(c);
}

void    ft_exit_fix(t_fix *fix, int i)
{
    int t;

    if (i == -2)
    {
        i = 0;
        while (fix->env && fix->env[i])
		    i++;
    }
    t = 0;
    while (t < i)
    {
        free(fix->env[t]);
        t++;
    }
    free(fix->env);
    exit(EXIT_FAILURE);
}