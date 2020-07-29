#include "../includes/minishell.h"

int    ft_redirection_right(t_command *c, char *line, int *i)
{
    if (line[*i + 1] && line[*i + 1]== '>')
    {
        *i = *i + 2;
        c->add = 2;
        return (ft_redir_right(c, line, i));
    }
    else
    {
        *i = *i + 1;
        c->add = 1;
        return (ft_redir_right(c, line, i));
    }
    return (0);
}

int    ft_redir_right(t_command *c, char *line, int *i)
{
    //printf("fd output = %c | i = %d | line[i] = '%c' \n", output, *i, line[*i]);
    while (line[*i] == ' ')
        *i = *i + 1;
    if (c->n_out[0] != '\0')
    {
        free(c->n_out);
        c->n_out = malloc(1);
        c->n_out[0] = '\0';
    }
    //printf("--> i = %d | line[i] = '%c' \n", *i, line[*i]);
    while (line[*i] != ' ' && line[*i] != '\0')
    {
        c->n_out = ft_realloc_concat(c->n_out, line[*i]);
        *i = *i + 1;
    }
    ft_touch(c);
    return (0);
}

void    ft_touch(t_command *c)
{
    int fd;

    if (c->add == 1)
        fd = open(c->n_out, O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | \
        S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    else if (c->add == 2)
        fd = open(c->n_out, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | \
        S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    close(fd);
}

int    ft_redirection_left(t_command *c, char *line, int *i)
{
    *i = *i + 1;
    c->input = 1;
    while (line[*i] == ' ')
        *i = *i + 1;
    if (c->n_input[0] != '\0')
    {
        free(c->n_input);
        c->n_input = malloc(1);
        c->n_input[0] = '\0';
    }
    //printf("--> i = %d | line[i] = '%c' \n", *i, line[*i]);
    while (line[*i] != ' ' && line[*i] != '\0')
    {
        c->n_input = ft_realloc_concat(c->n_input, line[*i]);
        *i = *i + 1;
    }
    return (ft_checkfile(c));
}

int ft_checkfile(t_command *c)
{
    struct stat   buffer;

    if (stat(c->n_input, &buffer) != 0)
    {
        ft_putstr("Error : file or directory doesn't exist\n");
        //return (1);
    }
    return (0);
}