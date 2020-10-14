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
    fix->error = 0;
    return (1);
}

int ft_env(t_command *c, t_fix *fix, int fd)
{
    int     j;
    
    j = 0;
    if (ft_env_err(c, fd, fix) == -1)
        return (1);
    while (fix->env && fix->env[j])
    {
        ft_putstr_fd(fix->env[j], fd);
        ft_putchar_fd('\n', fd);
        j++;
    }
    if (c->arg[1] && !ft_strcmp(c->arg[1], "="))
        ft_putstr_fd("=\n", fd);
    fix->error = 0;
    return (1);
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
    fix->error = 0;
    return (1);
}

int ft_export(t_command *c, t_fix *fix, int fd)
{
    int egal;
    int i;
    int j;
    char **env2;
    int len;

    len = ft_env_len(fix);

    if (ft_check0_export(c, fd, fix) == -1)
        return (1);
    j = 1;
    while (c->arg[j])
    {
        if ((egal = ft_checkj_export(c, fd, fix, j)) == -1)
            return (1);
        i = ft_env_compare(fix, c->arg[j], egal);
        printf("i=%d\n", i);
      //  if (!(env2 = ft_env_cpy(fix, c->arg[j], i + 2, egal)))
        if (!(env2 = ft_env_cpy(fix, c->arg[j], i, egal)))
            return (0);
        j++;
    }
    j = 0;
    while (fix->env[j])
    {
        free(fix->env[j]);
        j++;
    }
    printf("free env export=%d len init=%d\n", j, len);
    fix->env = NULL;
    fix->env = env2;
    len = ft_env_len(fix);
    printf("len fin=%d\n", len);
    fix->error = 0;
    return (1);
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
            fix->error = 1;
            return (1);
        }
        len = ft_env_len(fix);
        l = ft_env_compare(fix, c->arg[1], ft_strlen(c->arg[1]));
        if (len == l)
        {
            fix->error = 0;
            return (1);
        }
        if (!(env2 = ft_env_cpy(fix, c->arg[1], len, ft_strlen(c->arg[1]))))
            return (0);
    }
    env2[l] = NULL;
    fix->env = env2;
    fix->error = 0;
    return (1);
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
    if (ret == -1)
    {
        fix->error = 1;
        ft_putstr_fd("bash: cd: ", 2);
        ft_putstr_fd(c->arg[1], 2);
        ft_putstr_fd(": Aucun fichier ou dossier de ce type\n", 2);
        return (1);
    }
    if (!(getcwd(buf, PATH_MAX)))
        return (0);
    if (!(fix->env = ft_realloc_env(fix, buf)))
        return (0);
    fix->error = 0;
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
    fix->error = fix->exit;
    return (0);
}