#include "../includes/minishell.h"

int    ft_touch(t_command *c)
{
    int fd;
    if (c->add == 1)
        fd = open(c->n_out, O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | \
        S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    else if (c->add == 2)
        fd = open(c->n_out, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | \
        S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (fd == -1)
        return (0);
    return (ft_close_redir(c, fd));
}

int ft_open_redir(t_command *c)
{
    int fd;

    if (c->add == 0)
        fd = 1;
    else if (c->add == 1)
        fd = open(c->n_out, O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | 
        S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    else
        fd = open(c->n_out, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | 
        S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    return (fd);
}

int    ft_close_redir(t_command *c, int fd)
{
    printf("fd=%d\n", fd);
    if (c->add != 0)
    {
        if (close(fd) == -1)
            return (0);
    }
    return (1);
}

int ft_checkfile(t_command *c)
{
    struct stat   buffer;

    if (stat(c->n_input, &buffer) != 0)
    {
        ft_putstr_fd("bash: ", 2);
        ft_putstr_fd(c->n_input, 2);
        ft_putstr_fd(": Aucun fichier ou dossier de ce type\n", 2);
        return (-1);
    }
    return (1);
}