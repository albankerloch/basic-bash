#include "../includes/minishell.h"

void ft_execve(t_command *c, t_fix *fix)
{
    int fd;
    int fdi;
    int ret;
    
    ret = 0;
    if ((fd = ft_open_redir(c)) == -1)
        exit (-1);
    if (c->add != 0)
    {
        if (dup2(fd, 1) == -1)
        {
            close(fd);
            exit (-1);
        }
    }
    if (c->input == 1)
    {
        if ((fdi = open(c->n_input, O_RDONLY, S_IRUSR | S_IWUSR | 
        S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) == -1)
            exit (-1);
        if (dup2(fdi, 0) == -1)
        {
            if (c->add != 0)
                close(fd);
            close(fdi);
            exit (-1);
        }
    }
    if (c->arg[0][0] == '/' || c->arg[0][0] == '.')
        ret = execve(c->arg[0], c->arg, fix->env);
    else
    {
        if (ft_relative_path(c, fix) == ft_env_len(fix))
            ret = -1;
    }
    if (ret == -1)
    {
        fix->error = 127;
        ft_putstr_fd(c->arg[0], 2);
        ft_putstr_fd(" : commande introuvable\n", 2);
    }
    if (c->add != 0)
        close(fd);
    if (c->input == 1)
        close(fdi);
    exit(-1);
}

int   ft_relative_path(t_command *c, t_fix *fix)
{
    int j;
    int k;
    int len;
    char try_path[PATH_MAX];
    
    try_path[0] = '\0';
    len = 0;
    j = 0;
    while (fix->env && fix->env[j])
    {
        if (ft_strncmp(fix->env[j], "PATH", ft_strlen("PATH")) == 0)
        {
            k = 5;
            while (1)
            {
                if (fix->env[j][k] != ':' && fix->env[j][k])
                    ft_realloc_concat_buff(try_path, fix->env[j][k], &len);
                else
                {
                    ft_realloc_concat_buff(try_path, '/', &len);
                    ft_strjoin_buff(try_path, c->arg[0]);
                    execve(try_path, c->arg, fix->env);
                    ft_memset(try_path, '\0', ft_strlen(try_path));
                    if (!fix->env[j][k])
                        return (ft_env_len(fix));
                }
                k++;
            }
        }
        j++;
    }
    return (j);
}