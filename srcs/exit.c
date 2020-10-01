#include "../includes/minishell.h"

int    ft_exit_fix(t_fix *fix, int i)
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