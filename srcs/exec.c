#include "../includes/minishell.h"

void ft_execve(t_command *c, char **envp)
{
    int fd;
    int fdi;
    
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
    if (c->arg[0][0] == '/' || c->arg[0][0] == '.')
        execve(c->arg[0], c->arg, envp);
    else
       ft_relative_path(c, envp);
    if (c->add == 1 || c->add == 2)
        close(fd);
    if (c->input == 1)
        close(fdi);
}

int    ft_relative_path(t_command *c, char **envp)
{
    int j;
    int k;
    char *try_path;
    char *new;
    int ret;

    try_path = malloc(1);
    try_path[0] = '\0';
    j = 0;
    while (envp && envp[j])
    {
        if (envp[j] && ft_strncmp(envp[j], "PATH", ft_strlen("PATH")) == 0)
        {
            k = 5;
            while (envp[j] && envp[j][k])
            {
                if (envp[j][k] != ':')
                    try_path = ft_realloc_concat(try_path, envp[j][k]);
                else
                {
                    try_path = ft_realloc_concat(try_path, '/');
                    new = ft_strjoin(try_path, c->arg[0]);
                    ret = execve(new, c->arg, envp);
                    //si pas d'exit, c'est que execve return -1 -> alors cherche le chemin suivant de la variable PATH
                    free(try_path);
                    try_path = malloc(1);
                    try_path[0] = '\0';
                    free(new);
                 //   printf("relative ret = %d\n", ret);
                    if (ret == 0)
                        return (0);
                }
                k++;
            }
        }
        j++;
    }
    return (0);
}

int ft_redir(t_command *c)
{
    int fd;

    if (c->add == 0)
        return (1);
    else if (c->add == 1)
        fd = open(c->n_out, O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | 
        S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    else
        fd = open(c->n_out, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | 
        S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    return (fd);
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

void ft_exec(t_list *t, char *line, char ***envp)
{
    pid_t   pid;
    pid_t   pid2;
    int     pipe_fd[2];
    int     ret;
    int     save_fd;
    char    ***p;

    //aff_list(t);
    if (!t->next)
        fork_exec_cmd(t->content, line, envp);
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

            fork_exec_cmd(t->content, line, envp);
    
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

            ft_exec(t, line, envp);

            dup2(save_fd, 0);
            close(save_fd);
            (void)wait(NULL);
        }
    }
}

int ft_exec_cmd(t_command *c, char *line, char ***envp)
{
    int i;
    int j = 0;
    int n = 0;
    char **env2;
    int fd;

    fd = ft_redir(c);
    if (ft_strncmp(c->arg[0], "echo", ft_strlen("echo")) == 0  && ft_strlen("echo") == ft_strlen(c->arg[0]))
    {
       
        i = 1;
        if (ft_strncmp(c->arg[1], "-n", ft_strlen("-n")) == 0 && ft_strlen("-n") == ft_strlen(c->arg[1]))
        {
            n = 1;
            i++;
        }
        while(c->arg[i])
        {
            ft_putstr_fd(c->arg[i], fd);
            if (c->arg[i + 1])
                ft_putchar_fd(' ', fd);
            i++;
        }
        if (n == 0)
            ft_putchar_fd('\n', fd);
        if (c->add != 0)
            close(fd);
        return (0);
    }
    else if (ft_strncmp(c->arg[0], "env", ft_strlen("env")) == 0  && ft_strlen("env") == ft_strlen(c->arg[0]))
    {
        while (*envp && (*envp)[j])
        {
            ft_putstr_fd((*envp)[j], fd);
            ft_putchar_fd('\n', fd);
            j++;
        }
        if (c->add != 0)
            close(fd);
        return (0);
    }
    else if (ft_strncmp(c->arg[0], "pwd", ft_strlen("pwd")) == 0  && ft_strlen("pwd") == ft_strlen(c->arg[0]))
    {
        while (*envp && (*envp)[j])
        {
            if ((*envp)[j] && ft_strncmp((*envp)[j], "PWD", ft_strlen("PWD")) == 0)
            {
                ft_putstr_fd(ft_substr((*envp)[j], 4, ft_strlen((*envp)[j]) - 4), fd);
                ft_putchar_fd('\n', fd);
            }
            j++;
        }
        if (c->add != 0)
            close(fd);
        return (0);
    }
    else if (ft_strncmp(c->arg[0], "export", ft_strlen("export")) == 0  && ft_strlen("export") == ft_strlen(c->arg[0]))
    {
        while (*envp && (*envp)[j])
            j++;
        env2 = malloc(sizeof(char **) * j + 2);
        j = 0;
        while (*envp && (*envp)[j])
        {
            env2[j] = ft_strdup((*envp)[j]);
            j++;
        }
        env2[j] = ft_strdup(c->arg[1]);
        env2[j + 1] = NULL;
        *envp = env2;
        return (0);
    }
    else if (ft_strncmp(c->arg[0], "unset", ft_strlen("unset")) == 0  && ft_strlen("unset") == ft_strlen(c->arg[0]))
    {
        while (*envp && (*envp)[j])
            j++;
        int l = 0; //verif pour ne pas modifier l'env inutilement
        while (*envp && (*envp)[l])
        {
            if ((*envp)[l] && ft_strncmp((*envp)[l], c->arg[1], ft_strlen(c->arg[1])) == 0)
                break;
            l++;
        }
        if (j == l || c->env == 1)
            return (0);
        env2 = malloc(sizeof(char **) * j);
        j = 0;
        int i = 0;
        while (*envp && (*envp)[j])
        {
            if ((*envp)[j] && ft_strncmp((*envp)[j], c->arg[1], ft_strlen(c->arg[1])) == 0 && (*envp)[j][ft_strlen(c->arg[1])] == '=')
                i--;
            else
                env2[i] = ft_strdup((*envp)[j]);
            i++;
            j++;
        }
        env2[j] = NULL;
        *envp = env2;
        return (0);
    }
    else if (ft_strncmp(c->arg[0], "cd", ft_strlen("cd")) == 0  && ft_strlen("cd") == ft_strlen(c->arg[0]))
    {
        int ret = chdir(c->arg[1]);
        char *buf;
        buf = malloc(sizeof(char) * PATH_MAX);
        getcwd(buf, PATH_MAX);
        while (*envp && (*envp)[j])
            j++;
        env2 = malloc(sizeof(char **) * j + 1);
        j = 0;
        while (*envp && (*envp)[j])
        {
            if ((*envp)[j] && ft_strncmp((*envp)[j], "PWD", ft_strlen("PWD")) == 0)
            {
                env2[j] = ft_strjoin("PWD=", buf);
            }
            else
                env2[j] = ft_strdup((*envp)[j]);
            
            j++;
        }
        env2[j] = NULL;
  //      ft_env_destroy(*envp);
        *envp = env2;
        return (0);
    }
    else if (ft_strncmp(c->arg[0], "exit", ft_strlen("exit")) == 0  && ft_strlen("exit") == ft_strlen(c->arg[0]))
        exit(0);
    return (-1);
}

void    fork_exec_cmd(t_command *c, char *line, char ***envp)
{
    pid_t   pidf;
    char    ***p;
    int ret;
    
    if (ft_strncmp(c->arg[0], "exit", ft_strlen("exit")) == 0  && ft_strlen("exit") == ft_strlen(c->arg[0]))
        exit (0);
    ret = ft_exec_cmd(c, line, envp);
    if (ret == -1)
    {
        pidf = fork();
        signal(SIGINT, ft_sig_handler_process);
        if (pidf == 0)
            ft_execve(c, *envp);
        else
            (void)wait(NULL);
    }
}