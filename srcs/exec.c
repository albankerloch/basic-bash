#include "../includes/minishell.h"

int ft_exec(t_list *t, char *line, t_fix *fix)
{
    pid_t   pid;
    pid_t   pid2;
    int     pipe_fd[2];
    int     save_fd;
    int     error;

    error = 1;
    if (!t->next)
        return(fork_exec_cmd(t->content, line, fix));
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
            if (fork_exec_cmd(t->content, line, fix) == 0)
                exit(-1);
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
        return (0);
    return (1);
}

int ft_builtins(t_command *c, char *line, t_fix *fix, int fd)
{
    if (ft_strncmp(c->arg[0], "echo", ft_strlen("echo")) == 0  && ft_strlen("echo") == ft_strlen(c->arg[0]))
        return (ft_echo(c, fix, fd));
    else if (ft_strncmp(c->arg[0], "env", ft_strlen("env")) == 0  && ft_strlen("env") == ft_strlen(c->arg[0]))
        return (ft_env(c, fix, fd));
    else if (ft_strncmp(c->arg[0], "pwd", ft_strlen("pwd")) == 0  && ft_strlen("pwd") == ft_strlen(c->arg[0]))
        return (ft_pwd(c, fix, fd));
    else if (ft_strncmp(c->arg[0], "export", ft_strlen("export")) == 0  && ft_strlen("export") == ft_strlen(c->arg[0]))
        return (ft_export(c, fix, fd));
    else if (ft_strncmp(c->arg[0], "unset", ft_strlen("unset")) == 0  && ft_strlen("unset") == ft_strlen(c->arg[0]))
        return (ft_unset(c, fix, fd));
    else if (ft_strncmp(c->arg[0], "cd", ft_strlen("cd")) == 0  && ft_strlen("cd") == ft_strlen(c->arg[0]))
        return (ft_cd(c, fix, fd));
    else if (ft_strncmp(c->arg[0], "exit", ft_strlen("exit")) == 0  && ft_strlen("exit") == ft_strlen(c->arg[0]))
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
    }
    if (c->add != 0)
        close(fd);
    if (fix->error != 0)
    {
        fix->error = 127;
        return (0);
    }
    return (1);
}