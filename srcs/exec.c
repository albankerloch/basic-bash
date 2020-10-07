#include "../includes/minishell.h"

void aff_arg(t_list *begin)
{
    t_command *c;
    int i;

    c = begin->content;
    i = 0;
    while(c->arg [i])
    {
        printf(" ==> arg %d %s\n", i, c->arg[i]);
        i++;
    }
}

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
            printf("%d arg %d %s\n", k, i, c->arg[i]);
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
    int     ret;
    int     save_fd;
    char    ***p;

    //aff_list(t);
    if (!t->next)
        return(fork_exec_cmd(t->content, line, fix));
    else
    {
        pipe(pipe_fd);
        pid = fork();
        if (pid == 0)
        {
            save_fd = dup(1);
            close(pipe_fd[0]);
            dup2(pipe_fd[1], 1);
            close(pipe_fd[1]);
            fork_exec_cmd(t->content, line, fix);
            dup2(save_fd, 1);
            close(save_fd);
            exit(0);
        }
        else
        {
            t = t->next;
           // aff_arg(t);

            save_fd = dup(0);
            close(pipe_fd[1]);       
            dup2(pipe_fd[0], 0);
            close(pipe_fd[0]);

            ft_exec(t, line, fix);

            dup2(save_fd, 0);
            close(save_fd);
            (void)wait(NULL);
        }
    }
    return (1);
}

int ft_builtins(t_command *c, char *line, t_fix *fix)
{
    int fd;

    if ((fd = ft_open_redir(c)) == -1)
        return (0);
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
    {
        ft_putstr("exit\n");
        if (c->arg[1])
	        fix->exit = ft_atoi(c->arg[1]);
        else
            fix->exit = 0;
        return (0);
    }
    return (-1);
}

int    fork_exec_cmd(t_command *c, char *line, t_fix *fix)
{
    pid_t   pidf;
    char    ***p;
    int ret;
    
    if ((ret = ft_builtins(c, line, fix)) == 0)
        return (0);
    else if (ret == -1)
    {
        pidf = fork();
        signal(SIGINT, ft_sig_handler_process);
		signal(SIGQUIT, SIG_DFL);
        if (pidf == 0)
            ft_execve(c, fix);
        else
            wait(&(fix->error));
    }
    return (1);
}