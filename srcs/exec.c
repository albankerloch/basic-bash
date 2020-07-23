
#include "../includes/minishell.h"

int ft_exec(t_command c, char *line)
{
	char *envir[] = { NULL };
    int i;

    printf("c.arg[0]=%s\n", c.arg[0]);
    /*
	if (c.arg == NULL)
    {
        printf("quote ouvert\n");
        return (1);
    }
    arg = ft_split(c.arg, ' ');
    */
    if (ft_strncmp(c.arg[0], "echo", ft_strlen("echo")) == 0  && ft_strlen("echo") == ft_strlen(c.arg[0]))
    {
      //  printf("arg0=%s\n", arg[0]);
        //printf("arg1=%s\n", arg[1]);
        i = 1;
        while(c.arg[i])
        {
            ft_putstr(c.arg[i]);
            if (c.arg[i + 1])
                ft_putchar(' ');
            i++;
        }
        ft_putchar('\n');
    }
    else if (execve(c.arg[0], c.arg, envir) == -1)
    {
        ft_putchar('\n');
    }
    return (0);
}

void    ft_sub_arg(char **arg, int i)
{
    char   *sub_arg;
    int    j;

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