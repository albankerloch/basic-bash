#include "../includes/minishell.h"

int ft_echo(t_command *c, t_fix *fix, int fd)
{
    int i;
    int n;

    n = 0;
    if (c->arg[1])
    {
        ft_echo_n(&n, c->arg[1], &i);
        if (ft_strncmp(c->arg[i], "$?", ft_strlen("$?")) == 0 && ft_strlen("$?") == ft_strlen(c->arg[i]))
            ft_putnbr_fd(fix->error, fd);
        else
        {
            while(c->arg[i])
            {
                ft_putstr_fd(c->arg[i], fd);
                if (c->arg[i + 1])
                    ft_putchar_fd(' ', fd);
                i++;
            }
        }
    }
    if (n == 0)
        ft_putchar_fd('\n', fd);
    return (ft_close_redir(c, fd));
}

int ft_env(t_command *c, t_fix *fix, int fd)
{
    int     j;
    
    j = 0;
    if (ft_env_err(c, fd, fix) == -1)
        return (ft_close_redir(c, fd));
    while (fix->env && fix->env[j])
    {
        ft_putstr_fd(fix->env[j], fd);
        ft_putchar_fd('\n', fd);
        j++;
    }
    if (c->arg[1] && !ft_strcmp(c->arg[1], "="))
        ft_putstr_fd("=\n", fd);
    return (ft_close_redir(c, fd));
}

int ft_pwd(t_command *c, t_fix *fix, int fd)
{
    int j;
    char    *sub_str;

    j = 0;
    while (fix->env && fix->env[j])
    {
        if (fix->env[j] && ft_strncmp(fix->env[j], "PWD", ft_strlen("PWD")) == 0)
        {
            if (!(sub_str = ft_substr(fix->env[j], 4, ft_strlen(fix->env[j]) - 4)))
                return (0);
            ft_putstr_fd(sub_str, fd);
            free(sub_str);
            ft_putchar_fd('\n', fd);
        }
        j++;
    }
    return (ft_close_redir(c, fd));
}

int ft_export(t_command *c, t_fix *fix, int fd)
{
    int n;
    int i;
    char **env2;

    if ((n = ft_syntax_export(c, fd, fix)) == -1)
        return (ft_close_redir(c, fd));
    i = ft_env_compare(fix, c->arg[1], n);
    if (!(env2 = ft_env_cpy(fix, c->arg[1], i + 2, n)))
        return (0);
    if (!(env2[i] = ft_strdup(c->arg[1])))
        return (0);
    env2[i + 1] = NULL;
    return (ft_close_redir(c, fd));
}

int ft_unset(t_command *c, t_fix *fix, int fd)
{
    int len;
    int l;
    char **env2;

    if (c->arg[1])
    {
        if (ft_strcmp(c->arg[1], "$") == 0)
        {
            ft_putstr_fd("bash: unset: \" $ \" : identifiant non valable\n", 2);
            return (ft_close_redir(c, fd));
        }
        len = ft_env_len(fix);
        l = ft_env_compare(fix, c->arg[1], ft_strlen(c->arg[1]));
        if (len == l)
            return (ft_close_redir(c, fd));
        if (!(env2 = ft_env_cpy(fix, c->arg[1], len, ft_strlen(c->arg[1]))))
            return (0);
        env2[l] = NULL;
    }
    return (ft_close_redir(c, fd));
}

int ft_cd(t_command *c, t_fix *fix, int fd)
{
    int ret;
    char    buf[PATH_MAX];
    int j;
    
    if (!c->arg[1])
        ret = chdir("/home/user42");
    else
        ret = chdir(c->arg[1]);
    getcwd(buf, PATH_MAX);
    if (!(fix->env = ft_realloc_env(fix, buf)))
        return (0);
    return (ft_close_redir(c, fd));
}