#include "../includes/minishell.h"

int ft_echo(t_command *c, t_fix *fix, int fd)
{
    int i;
    int j;
    int n;
    char    *val_var;
    char    *arg;

    i = 1;
    n = 0;
    if (ft_strncmp(c->arg[i], "-n", ft_strlen("-n")) == 0 && ft_strlen("-n") == ft_strlen(c->arg[i]))
    {
        n = 1;
        i++;
    }
    if (ft_strncmp(c->arg[i], "$?", ft_strlen("$?")) == 0 && ft_strlen("$?") == ft_strlen(c->arg[i]))
        ft_putnbr_fd(fix->error, fd);
    else
    {
        while(c->arg[i])
        {
            ft_putstr_fd(c->arg[i], fd);
            if (c->arg[i][j + 1] == '\0' && c->arg[i + 1])
                ft_putchar_fd(' ', fd);
            i++;
        }
    }
    if (n == 0)
        ft_putchar_fd('\n', fd);
    ft_close_redir(c, fd);
    return (0);
}

int ft_env(t_command *c, t_fix *fix, int fd)
{
    int     j;
    
    j = 0;
    while (fix->env && fix->env[j])
    {
        ft_putstr_fd(fix->env[j], fd);
        ft_putchar_fd('\n', fd);
        j++;
    }
    ft_close_redir(c, fd);
    return (0);
}

int ft_pwd(t_command *c, t_fix *fix, int fd)
{
    int j;

    j = 0;
    while (fix->env && fix->env[j])
    {
        if (fix->env[j] && ft_strncmp(fix->env[j], "PWD", ft_strlen("PWD")) == 0)
        {
            ft_putstr_fd(ft_substr(fix->env[j], 4, ft_strlen(fix->env[j]) - 4), fd);
            ft_putchar_fd('\n', fd);
        }
        j++;
    }
    ft_close_redir(c, fd);
    return (0);
}

int ft_export(t_command *c, t_fix *fix, int fd)
{
    int n;
    int i;
    char **env2;

    if ((n = ft_syntax_export(c, fd, fix)) == 1)
    {
        ft_close_redir(c, fd);
        return (1);
    }
    i = ft_env_compare(fix, c->arg[1], n);
    env2 = ft_env_cpy(fix, c->arg[1], i + 2, n);
    env2[i] = ft_strdup(c->arg[1]);
    env2[i + 1] = NULL;
    ft_close_redir(c, fd);
    return (0);
}

int ft_unset(t_command *c, t_fix *fix, int fd)
{
    int len;
    int l;
    char **env2;

    len = ft_env_len(fix);
    l = 0;
    while (fix->env && fix->env[l])
    {
        if (fix->env[l] && ft_strncmp(fix->env[l], c->arg[1], ft_strlen(c->arg[1])) == 0)
            break;
        l++;
    }
    if (len == l)
        return (0);
    env2 = ft_env_cpy(fix, c->arg[1], len, ft_strlen(c->arg[1]));
    env2[len] = NULL;
    ft_close_redir(c, fd);
    return (0);
}

int ft_cd(t_command *c, t_fix *fix, int fd)
{
    int ret;
    char    *buf;
    int j;
    char    **env2;
    
    ret = chdir(c->arg[1]);
    buf = malloc(sizeof(char) * PATH_MAX);
    getcwd(buf, PATH_MAX);
    j = 0;
    while (fix->env && fix->env[j])
        j++;
    env2 = malloc(sizeof(char **) * j + 1);
    j = 0;
    while (fix->env && fix->env[j])
    {
        if (fix->env[j] && ft_strncmp(fix->env[j], "PWD", ft_strlen("PWD")) == 0)
        {
            env2[j] = ft_strjoin("PWD=", buf);
        }
        else
            env2[j] = ft_strdup(fix->env[j]);
        j++;
    }
    env2[j] = NULL;
    fix->env = env2;
    ft_close_redir(c, fd);
    return (0);
}