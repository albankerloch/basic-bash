#include "../includes/minishell.h"

void ft_execve(t_command *c, t_fix *fix)
{
    int fd;
    int fdi;
    int ret;
    int j;
    
    ret = 0;
    fd = 1;
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
        fix->error = execve(c->arg[0], c->arg, fix->env);
    else
    {
        j = ft_relative_path(c, fix);
        if (j == ft_env_len(fix))
            fix->error = -1;
    }
    if (fix->error == -1)
    {
        ft_putstr_fd(c->arg[0], 2);
        ft_putstr_fd(" : commande introuvable\n", 2);
    }
    if (c->add == 1 || c->add == 2)
        close(fd);
    if (c->input == 1)
        close(fdi);
    exit(-1);
}

int   ft_relative_path(t_command *c, t_fix *fix)
{
    int j;
    int k;
    char try_path[PATH_MAX];
    
    try_path[0] = '\0';
    j = 0;
    while (fix->env && fix->env[j])
    {
        if (ft_strncmp(fix->env[j], "PATH", ft_strlen("PATH")) == 0)
        {
            k = 5;
            while (1)
            {
                if (fix->env[j][k] != ':' && fix->env[j][k])
                    ft_realloc_concat_buff(try_path, fix->env[j][k]);
                else
                {
                    ft_realloc_concat_buff(try_path, '/');
                    ft_strjoin_buff(try_path, c->arg[0]);
                    fix->error = execve(try_path, c->arg, fix->env);
                    ft_memset(try_path, '\0', ft_strlen(try_path));
                    if (!fix->env[j][k])
                        return (j);
                }
                k++;
            }
        }
        j++;
    }
    return (j);
}