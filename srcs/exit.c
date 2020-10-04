#include "../includes/minishell.h"

void    ft_exit(t_fix *fix, t_list *t, char *line, int e)
{
    free(line);
	ft_lstclear(&t, &ft_del_command);
    ft_exit_fix(fix, -2, e);
}

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

void    ft_del_command(void *c)
{
    ft_free_command(c);
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

int    ft_exit_fix(t_fix *fix, int i, int e)
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
    if (e == EXIT_FAILURE)
        ft_putstr("malloc error\n");
    exit(e);
}