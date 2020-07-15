
#include "../includes/minishell.h"

int ft_exec(t_command c, char *line)
{
    if (ft_strncmp(line, "echo", c.k_end - c.k_begin + 1))
    {
        ft_putstr(ft_substr(line, c.a_begin, c.a_end - c.a_begin + 1));
        ft_putchar('\n');
    }

    return (0);
}