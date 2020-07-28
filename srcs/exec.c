#include "../includes/minishell.h"

void ft_execve(t_command *c)
{
    int fd;
    char *envir[] = { NULL };

    if (c->add == 1)
        fd = open(c->n_out, O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | 
        S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    else
        fd = open(c->n_out, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | 
        S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    dup2(fd, 1);
    execve(c->arg[0], c->arg, envir);
    close(fd);
}

void ft_redir_echo(t_command *c)
{
    int fd;
    int i;
    char ch;

    if (c->add == 1)
        fd = open(c->n_out, O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | 
        S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    else
        fd = open(c->n_out, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | 
        S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    i = 1;
    while(c->arg[i])
    {
        write(fd, c->arg[i], ft_strlen(c->arg[i]));
        if (c->arg[i + 1])
            write(fd, " ", 1);
        //printf("%d --> %s\n", i, c->arg[i]);
        i++;
    }
    ch = '\n';
    write(fd, &ch, 1);
    close(fd);
}

int ft_exec(t_command c, char *line)
{
    int i;
    
    /*
    i = 0;
    while(c.arg [i])
    {
        printf("arg %d %s\n", i, c.arg[i]);
        i++;
    }
    ft_putstr(c.arg[0]);*/
    if (ft_strncmp(c.arg[0], "echo", ft_strlen("echo")) == 0  && ft_strlen("echo") == ft_strlen(c.arg[0]))
    {
        if (c.add == 0)
        {
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
        else
        {
            ft_redir_echo(&c);
        }
    }
    else
    {
        ft_execve(&c);
        ft_putchar('\n');
    }
    return (0);
}