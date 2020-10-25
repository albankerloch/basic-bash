#include "../includes/minishell.h"

int ft_echo(t_command *c, t_fix *fix, int fd)
{
    int i;
    int n;

    n = 0;
    if (c->arg[1])
    {
        i = 1;
        ft_echo_n(&n, c->arg, &i);
        while(c->arg[i])
        {
            ft_putstr_fd(c->arg[i], fd);
            if (c->arg[i + 1])
                ft_putchar_fd(' ', fd);
            i++;
        }
    }
    if (n == 0)
        ft_putchar_fd('\n', fd);
    return (1);
}

int ft_env(t_command *c, t_fix *fix, int fd)
{
    int     j;
    
    j = 0;
    if (ft_env_err(c, fd, fix) == -1)
        return (2);
    while (fix->env && fix->env[j])
    {
        ft_putstr_fd(fix->env[j], fd);
        ft_putchar_fd('\n', fd);
        j++;
    }
    if (c->arg[1] && !ft_strcmp(c->arg[1], "="))
        ft_putstr_fd("=\n", fd);
    return (1);
}

int ft_pwd(t_command *c, t_fix *fix, int fd)
{
    int j;
    char    here[PATH_MAX];

    if (!(getcwd(here, PATH_MAX)))
    {
        ft_error(errno);
        return (0);
    }
    ft_putstr_fd(here, fd);
    ft_putchar_fd('\n', fd);
    return (1);
}

int ft_export(t_command *c, t_fix *fix, int fd)
{
    int i;
    int j;

    if (!c->arg[1])
        return (ft_export_without_arg(fix, fd));
    i = 1;
    while (c->arg[i])
    {
        j = 0;
        while (c->arg[i][j])
        {
            if (c->arg[i][j] == '=')
            {
                if ((!(ft_export_check_id(c->arg[i], j, fix))) || (c->arg[i][j - 1] == '_' && j == 1))
                    return (2);
                if (!(fix->env = ft_replace_env(fix, c->arg[i], j)))
                    return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

int ft_unset(t_command *c, t_fix *fix, int fd)
{
    int i;

    i = 1;
    while (c->arg[i])
    {
        if (ft_export_check_id(c->arg[i], ft_strlen(c->arg[i]), fix) && (ft_env_len(fix) != ft_env_compare(fix, c->arg[i], ft_strlen(c->arg[i]))))
        {
            if (!(c->arg[i][0] == '_' && c->arg[i][1] == '\0'))
            {
                if (!(fix->env = ft_unset_env(fix, c->arg[i])))
                    return (0);
            }
        }
        i++;
    }
    return (1);
}

int ft_cd(t_command *c, t_fix *fix, int fd)
{
    int ret;
    char    buf[PATH_MAX];

    if (!c->arg[1])
        ret = chdir("/home/user42");
    else
        ret = chdir(c->arg[1]);
    if (ret == -1)
    {
        fix->error = 1;
        ft_error(errno);
        return (2);
    }
    if (!(getcwd(buf, PATH_MAX)))
    {
        ft_error(errno);
        return (0);
    }
    if (!(fix->env = ft_realloc_env(fix, buf)))
    {
        ft_error(errno);
        return (0);
    }
    return (1);
}

int ft_builtin_exit(t_command *c, t_fix *fix, int fd)
{
    ft_putstr("exit\n");
    if (!(c->arg[1]))
        fix->exit = 0;
    else
    {
        if (!(ft_isnum(c->arg[1])))
        {
            ft_putstr_fd("bash: exit: ",2);
            ft_putstr_fd(c->arg[1] ,2);
            ft_putstr_fd(": argument numérique nécessaire\n", 2);
            fix->exit = 2;
         //   fix->error = 2;
        }
        else
        {
            if (!(c->arg[2]))
    	        fix->exit = (unsigned char)ft_atoi(c->arg[1]);
            else
            {
                ft_putstr_fd("bash: exit: trop d'arguments\n", 2);
                fix->error = 1;
                return (1);
            }
        } 
    }
    return (0);
}