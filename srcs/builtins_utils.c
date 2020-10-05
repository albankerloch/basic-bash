#include "../includes/minishell.h"

void    ft_echo_n(int *n, char *arg, int *i)
{
    if (ft_strncmp(arg, "-n", ft_strlen("-n")) == 0 && ft_strlen("-n") == ft_strlen(arg))
    {
        *n = 1;
        *i = 2;
    }
    else
        *i = 1;
}

int    ft_env_len(t_fix *fix)
{
    int len;

    while (fix->env && fix->env[len])
        len++;
    return (len);
}

int ft_env_compare(t_fix *fix, char *arg, int n)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (fix->env && fix->env[j])
    {
        if (ft_strncmp(arg, fix->env[j], n) == 0 && fix->env[j][n] == '=')
            i--;
        j++;
        i++;
    }
    return (i);
}

char **ft_env_cpy(t_fix *fix, char *arg, int len, int egal)
{
    char    **env2;
    char    *val_var;
    int i;
    int j;

    if (!(env2 = malloc(sizeof(char **) * len)))
        return (NULL);
    len = 0;
    i = 0;
    j = 0;
    while (fix->env && fix->env[j])
    {
        if (fix->env[j] && ft_strncmp(fix->env[j], arg, egal) == 0 && fix->env[j][egal] == '=')
            i--;
        else
        {
            if (!(env2[i] = ft_strdup(fix->env[j])))
                return (NULL);
        }
        i++;
        j++;
    }
    fix->env = env2;
    return (env2);
}

int ft_env_err(t_command *c, int fd, t_fix *fix)
{
    if (c->arg[1] && ft_strcmp(c->arg[1], "=") && ft_strcmp(c->arg[1], "-"))
    {
        ft_putstr_fd("env: \"", fd);
        ft_putstr_fd(c->arg[1], fd);
        ft_putstr_fd("\": Aucun fichier ou dossier de ce type\n", fd);
        return (-1);
    }
    else if (c->arg[1] && !ft_strcmp(c->arg[1], "-"))
        return (-1);
    return (1);
}

int ft_syntax_export(t_command *c, int fd, t_fix *fix)
{
    int i;
    int eg;
    
    if (!c->arg[1])
        return (ft_export_err(2, fd, 0, fix));
    if (c->arg[1] && c->arg[1][0] == '=')
        return (ft_export_err(3, fd, c->arg[1], fix));
    if (c->arg[2] && c->arg[2][0] == '=')
        return (ft_export_err(3, fd, c->arg[2], fix));
    eg = 0;
    i = 0;
    while (c->arg[1][i])
    {
        if (c->arg[1][i] == '=')
            return (i);
        i++;
    }
    return (ft_export_err(1, fd, 0, fix));
}

int ft_export_err(int err, int fd, char *arg, t_fix *fix)
{
    int j;
    char    *sub_str;

    j = 0;
    if (err == 2)
    {
        while (fix->env && fix->env[j])
        {
            ft_putstr_fd("declare -x ", fd);
            ft_putstr_fd(fix->env[j], fd);
            ft_putchar_fd('\n', fd);
            j++;
        }
    }
    else if (err == 3 || err == 4)
    {
        if (err == 4)
        {
            while (arg[j] != '=')
                j++;
        }
        ft_putstr_fd("bash: export: \" ", fd);
        if (err == 4)
        {
            if (!(sub_str = ft_substr(arg, j, ft_strlen(arg) - j)))
                return (0);
            ft_putstr_fd(sub_str, fd);
            free(sub_str);
        }
        else
            ft_putstr_fd(arg, fd);
        ft_putstr_fd(" \" : identifiant non valable\n", fd);
    }
    return (-1);
}