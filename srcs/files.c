/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 22:43:33 by aduchemi          #+#    #+#             */
/*   Updated: 2020/11/05 22:43:34 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    {
        ft_error(errno);
        return (-1);
    }
    if (c->add != 0)
        close(fd);
    return (1);
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
    if (fd == -1)
    {
        ft_error(errno);
        return (-1);
    }
    return (fd);
}

int ft_checkfile(t_command *c, t_fix *fix)
{
    struct stat   buffer;

    if (stat(c->n_input, &buffer) != 0)
    {
        ft_putstr_fd("bash: ", 2);
        ft_putstr_fd(c->n_input, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        fix->error = 1;
        return (-1);
    }
    return (1);
}
