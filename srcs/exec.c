
#include "../includes/minishell.h"

int ft_exec(t_command c, char *line)
{

	char **arg;
	char *envir[] = { NULL };
    int i;

/*
    if (ft_strncmp(&line[c.k_begin], "echo", ft_strlen("echo")) == 0 && ft_strlen("echo") == c.k_end - c.k_begin)
    {
        ft_putstr(ft_substr(&line[c.k_begin], c.a_begin, c.a_end - c.a_begin + 1));
        ft_putchar('\n');
    }
*/
	arg = ft_split(c.arg, ' ');

    if (ft_strncmp(arg[0], "echo", ft_strlen("echo")) == 0  && ft_strlen("echo") == ft_strlen(arg[0]))
    {
        i = 1;
        while(arg[i])
        {
            ft_putstr(arg[i]);
            i++;
        }
        ft_putchar('\n');
    }
    else
    	execve(arg[0], arg, envir);
    return (0);
}
