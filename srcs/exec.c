
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
	if (c.arg == NULL)
    {
        printf("erreur quote à gérer\n");
        return (1);
    }
    arg = ft_split(c.arg, ' ');
    if (ft_strncmp(arg[0], "echo", ft_strlen("echo")) == 0  && ft_strlen("echo") == ft_strlen(arg[0]))
    {
        i = 1;
        while(arg[i])
        {
            ft_sub_arg(arg, i);
            if (arg[i + 1])
                ft_putchar(' ');
            i++;
        }
        ft_putchar('\n');
    }
    else
    	execve(arg[0], arg, envir);
    return (0);
}

void    ft_sub_arg(char **arg, int i)
{
    char   *sub_arg;
    int j;

    sub_arg = ft_substr(arg[i], 0, ft_strlen(arg[i]));
    while (ft_strnstr(sub_arg, "\\n", ft_strlen(sub_arg)) != NULL)
    {
        j = 0;
        while (sub_arg[j] != '\\' && sub_arg[j + 1] && sub_arg[j + 1] != 'n')
        {
            ft_putchar(sub_arg[j]);
            j++;
        }
        ft_putchar('\n');
        j+=2;
        sub_arg = ft_substr(sub_arg, j, ft_strlen(sub_arg) - j);
    }
    ft_putstr(sub_arg);
}