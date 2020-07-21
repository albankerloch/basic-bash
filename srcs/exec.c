
#include "../includes/minishell.h"

int ft_exec(t_command c, char *line)
{

	char **arg;
	char *envir[] = { NULL };

	arg = ft_split(c.arg, ' ');
	execve(arg[0], arg, envir);
/*
    if (ft_strncmp(&line[c.k_begin], "echo", ft_strlen("echo")) == 0 && ft_strlen("echo") == c.k_end - c.k_begin)
    {
        ft_putstr(ft_substr(&line[c.k_begin], c.a_begin, c.a_end - c.a_begin + 1));
        ft_putchar('\n');
    }
*/
    return (0);
}
