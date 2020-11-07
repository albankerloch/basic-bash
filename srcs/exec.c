/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:24:18 by aduchemi          #+#    #+#             */
/*   Updated: 2020/07/15 16:59:40 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_parent_exec(t_list *t, char *line, t_fix *fix, int pipe_fd[2])
{
    int save_fd;

    t = t->next;
    if ((save_fd = dup(0)) == -1)
        return (0);
    close(pipe_fd[1]);
    if (dup2(pipe_fd[0], 0) == -1)
        return (0);
    close(pipe_fd[0]);
    if (ft_exec(t, line, fix) == 0)
        return (0);
    if (dup2(save_fd, 0) == -1)
        return (0);
    close(save_fd);
    return (1);
}

void    ft_child_exec(t_list *t, char *line, t_fix *fix, int pipe_fd[2])
{
    int     save_fd;
    int     ret;

    if ((save_fd = dup(1)) == -1)
        exit(-1);
    close(pipe_fd[0]);
    if (dup2(pipe_fd[1], 1) == -1)
        exit(-1);
    close(pipe_fd[1]);
    if ((ret = ft_fork_exec_cmd(t->content, line, fix)) == 0 || ret == -1)
        exit(-1);
    if (dup2(save_fd, 1) == -1)
        exit(-1);
    close(save_fd);
    exit(0);
}

int ft_exec(t_list *t, char *line, t_fix *fix)
{
    pid_t   pid;
    int     pipe_fd[2];
    int     error;

    error = 1;
    if (!t->next)
        return (ft_fork_exec_cmd(t->content, line, fix));
    else
    {
        pipe(pipe_fd);
        pid = fork();
        if (pid == 0)
            ft_child_exec(t, line, fix, pipe_fd);
        else
        {
            if (!(ft_parent_exec(t, line, fix, pipe_fd)))
                return (0);
            wait(&error);
        }
    }
    if (error != 0)
        return (-1);
    return (1);
}

int ft_builtins(t_command *c, char *line, t_fix *fix, int fd)
{
    if (ft_strcmp(c->arg[0], "echo") == 0)
        return (ft_echo(c, fd));
    else if (ft_strcmp(c->arg[0], "env") == 0)
        return (ft_env(c, fd));
    else if (ft_strcmp(c->arg[0], "pwd") == 0)
        return (ft_pwd(c, fd));
    else if (ft_strcmp(c->arg[0], "export") == 0)
        return (ft_export(c, fd));
    else if (ft_strcmp(c->arg[0], "unset") == 0)
        return (ft_unset(c, fd));
    else if (ft_strcmp(c->arg[0], "cd") == 0)
        return (ft_cd(c, fd));
    else if (ft_strcmp(c->arg[0], "exit") == 0)
        return (ft_builtin_exit(c, fd));
    return (-1);
}

void    ft_fork_execve(t_command *c, t_fix *fix)
{
    pid_t   pidf;
    int status;

    pidf = fork();
    if (pidf == 0)
    {
        signal(SIGINT, ft_sig_handler_process);
        signal(SIGQUIT, SIG_DFL);
        ft_execve(c, fix);
    }
    else
    {
        signal(SIGINT, ft_sig_handler_process);
        signal(SIGQUIT, ft_sig_handler_process);
        wait(&status);
    }
    if (WIFEXITED(status))
        fix->error  = WEXITSTATUS(status);
}

int    ft_fork_exec_cmd(t_command *c, char *line, t_fix *fix)
{
    char    ***p;
    int ret;
    int fd;

    if ((fd = ft_open_redir(c)) == -1)
        return (0);
    if ((ret = ft_builtins(c, line, fix, fd)) == 0)
    {
        if (c->add != 0)
            close(fd);
        return (0);
    }
    else if (ret == 1)
        fix->error = 0;
    else if (ret == -1)
        ft_fork_execve(c, fix);
    if (c->add != 0)
        close(fd);
    return (1);
}