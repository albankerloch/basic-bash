#include "../includes/minishell.h"

void aff_list(t_list *begin)
{
    t_command *c;
    int i;
    int k;

    k = 0;
    while(begin)
    {
        c = begin->content;
        i = 0;
        while(c->arg [i])
        {
            printf("%d arg %d |%s|\n", k, i, c->arg[i]);
            i++;
        }
        printf("  output stdout = %s \n", c->n_out);
        printf("  redir = %d \n", c->add);
        printf("  input stdin = %s \n", c->n_input);
        printf("  flag input = %d \n", c->input);
        k++;
        begin = begin->next;
    }
}

int ft_exec(t_list *t, char *line, t_fix *fix)
{
    pid_t   pid;
    pid_t   pid2;
    int     pipe_fd[2];
    int     save_fd;
    int     ret;
    int     error;

  //  aff_list(t);
    error = 1;
    t_command *c = t->content;
    ret = 0;
    if (!t->next)
        return (fork_exec_cmd(t->content, line, fix));
    else
    {
        pipe(pipe_fd);
        pid = fork();
        if (pid == 0)
        {
            if ((save_fd = dup(1)) == -1)
                exit(-1);
            close(pipe_fd[0]);
            if (dup2(pipe_fd[1], 1) == -1)
                exit(-1);
            close(pipe_fd[1]);
            if ((ret = fork_exec_cmd(t->content, line, fix)) == 0 || ret == -1)
            {
                error = -1;
                exit(-1);
            }    
            if (dup2(save_fd, 1) == -1)
                exit(-1);
            close(save_fd);
            exit(0);
        }
        else
        {
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
        return (ft_echo(c, fix, fd));
    else if (ft_strcmp(c->arg[0], "env") == 0)
        return (ft_env(c, fix, fd));
    else if (ft_strcmp(c->arg[0], "pwd") == 0)
        return (ft_pwd(c, fix, fd));
    else if (ft_strcmp(c->arg[0], "export") == 0)
        return (ft_export(c, fix, fd));
    else if (ft_strcmp(c->arg[0], "unset") == 0)
        return (ft_unset(c, fix, fd));
    else if (ft_strcmp(c->arg[0], "cd") == 0)
        return (ft_cd(c, fix, fd));
    else if (ft_strcmp(c->arg[0], "exit") == 0)
        return (ft_builtin_exit(c, fix, fd));
    return (-1);
}

int    fork_exec_cmd(t_command *c, char *line, t_fix *fix)
{
    pid_t   pidf;
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
    {
        pidf = fork();
        if (pidf == 0)
        {
            signal(SIGINT, ft_sig_handler_process);
		    signal(SIGQUIT, SIG_DFL);
            ft_execve(c, fix);
        }
        else
            wait(&(fix->error));
        if (fix->error != 0)
        {
            fix->error = 127;
            return (-1);
        }
    }
    if (c->add != 0)
        close(fd);
    return (1);
}