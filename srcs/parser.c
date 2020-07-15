/*best parser ever*/

#include "../includes/minishell.h"

t_command ft_parser(char *line)
{
    t_command   c;
    int         i;

    c.k_begin = 0;
    i = 0;
    while(line[i] != ' ' && line[i])
        i++;
    c.k_end = i;
    c.a_begin = i + 1;
    while(line[i] != '\0')
        i++;
    c.a_end = i;

 //   printf("%d %d %d %d\n", c.k_begin, c.k_end, c.a_begin, c.a_end);

    return (c);
}
