#include "../includes/minishell.h"

void ft_execve(t_command *c)
{
    int fd;
    int fdi;
    char *envir[] = { NULL };

   // printf("TEST TEST\n");
    if (c->add == 1)
        fd = open(c->n_out, O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | 
        S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    else if (c->add == 2)
        fd = open(c->n_out, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | 
        S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (c->add == 1 || c->add == 2)
        dup2(fd, 1);
    if (c->input == 1)
    {
        fdi = open(c->n_input, O_RDONLY, S_IRUSR | S_IWUSR | 
        S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
        dup2(fdi, 0);
    }
    execve(c->arg[0], c->arg, envir);
    if (c->add == 1 || c->add == 2)
        close(fd);
    if (c->input == 1)
        close(fdi);
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

int ft_exec(t_list *t, char *line)
{
    pid_t   pid;
    int     status;
    int     pipe_fd[2];
    int     k;
    char      buffer[1024];
    int       ret;

    aff_list(t);

  //  pid = fork();
  //  if (pid == 0)
  //  {
        pipe(pipe_fd);
        pid = fork();
        if (pid != 0)
        {
            printf("CMD1 ECHO LOL\n");
            aff_arg(t);
            close(pipe_fd[0]);
            dup2(pipe_fd[1], 1);
            ft_exec_cmd(t, t->content, line);
        }
        else
        {
            printf("CMD2 LS \n");
            t = t->next;
            aff_arg(t);
            close(pipe_fd[1]);
            /*
            while ((ret = read(pipe_fd[0], buffer, 1023)) != 0)
            {
                buffer[ret] = 0;
                printf("->> %s\n", buffer);
            }   
            */         
            dup2(pipe_fd[0], 0);
            ft_exec_cmd(t, t->content, line);
            //wait(&status);
        }
 //   }
 //   else
//        wait(&status);

    /*
    while (t)
    {
        if (k != 0)
            pipe(pipe_fd);
        pid = fork();
        if (pid == 0)
        {
            if (k != 0)
            {
                close(pipe_fd[0]);
                dup2(pipe_fd[0], 1);
            }
            else
            {
                close(pipe_fd[1]);
                dup2(pipe_fd[1], 0);
            }
            ft_exec_cmd(t, t->content, line);
        }
        else
            wait(&status);
        t = t->next;
    }
    */
    return (0);
}

int ft_exec_cmd(t_list *t, t_command *c, char *line)
{
    int i;

    if (ft_strncmp(c->arg[0], "echo", ft_strlen("echo")) == 0  && ft_strlen("echo") == ft_strlen(c->arg[0]))
    {
        if (c->add == 0)
        {
            i = 1;
            while(c->arg[i])
            {
                ft_putstr(c->arg[i]);
                if (c->arg[i + 1])
                    ft_putchar(' ');
                i++;
            }
            ft_putchar('\n');
        }
        else
        {
            ft_redir_echo(c);
        }
    }
    else
    {
        ft_execve(c);
        ft_putchar('\n');
    }
    return (0);
}