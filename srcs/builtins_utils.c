#include "../includes/minishell.h"

void    ft_echo_n(int *n, char *arg, int *i)
{
    if (!ft_strcmp(arg, "-n"))
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
        ft_putstr_fd("env: \"", 2);
        ft_putstr_fd(c->arg[1], 2);
        ft_putstr_fd("\": Aucun fichier ou dossier de ce type\n", 2);
        fix->error = 127;
        return (-1);
    }
    else if (c->arg[1] && !ft_strcmp(c->arg[1], "-"))
    {
        fix->error = 0;
        return (-1);
    }
    return (1);
}

int ft_syntax_export(t_command *c, int fd, t_fix *fix)
{
    int i;
    
    if (!c->arg[1])
    {
        i = 0;
        while (fix->env && fix->env[i])
        {
            ft_putstr_fd("declare -x ", 2);
            ft_putstr_fd(fix->env[i], 2);
            ft_putchar_fd('\n', 2);
            i++;
        }
        fix->error = 0;
        return (-1);
    }
    if (c->arg[1] && c->arg[1][0] == '=')
        return (ft_export_err(fd, c->arg[1], fix));
    if (c->arg[2] && c->arg[2][0] == '=')
        return (ft_export_err(fd, c->arg[2], fix));
    i = 0;
    while (c->arg[1][i])
    {
        if (c->arg[1][i] == '=')
            return (i);
        i++;
    }
    fix->error = 0;
    return (-1);
}

int ft_export_err(int fd, char *arg, t_fix *fix)
{
    char    *sub_str;

    ft_putstr_fd("bash: export: \" ", 2);
    ft_putstr_fd(arg, 2);
    ft_putstr_fd(" \" : identifiant non valable\n", 2);
    fix->error = 1;
    return (-1);
}

char **ft_realloc_env(t_fix *fix, char buf[PATH_MAX])
{
    int j;
    char    **env2;

    j = 0;
    while (fix->env && fix->env[j])
        j++;
    if (!(env2 = malloc(sizeof(char **) * j + 1)))
        return (NULL);
    j = 0;
    while (fix->env && fix->env[j])
    {
        if (fix->env[j] && ft_strncmp(fix->env[j], "PWD", ft_strlen("PWD")) == 0)
        {
            if (!(env2[j] = ft_strjoin("PWD=", buf)))
                return (ft_free_tab(env2, j));
        }
        else
        {
            if (!(env2[j] = ft_strdup(fix->env[j])))
                return (ft_free_tab(env2, j));
        }
        j++;
    }
    env2[j] = NULL;
    free(fix->env);
    return (env2);
}