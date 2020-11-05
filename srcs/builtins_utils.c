#include "../includes/minishell.h"

void    ft_echo_n(int *n, char **arg, int *i)
{
    while(arg[*i])
    {
        if (!ft_strcmp(arg[*i], "-n"))
        {
            *n = 1;
            (*i)++;
        }
        else
            break;
    }
}

int ft_env_compare(t_fix *fix, char *arg, int n)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (fix->env && fix->env[j])
    {
        if (ft_strncmp(arg, fix->env[j], n) == 0 && (fix->env[j][n] == '=' || fix->env[j][n] == '\0'))
            i--;
        j++;
        i++;
    }
    return (i);
}

int    ft_env_len(t_fix *fix)
{
    int len;

    len = 0;
    while (fix->env[len])
        len++;
    return (len);
}

char **ft_unset_env(t_fix *fix, char *arg)
{
    char    **env2;
    int i;
    int j;

    env2 = NULL;
    if (!(env2 = malloc(sizeof(char **) * ft_env_len(fix))))
        return (NULL);
    i = 0;
    j = 0;
    while (fix->env && fix->env[j])
    {
        if (!(ft_strncmp(fix->env[j], arg, ft_strlen(arg)) == 0))
        {
            env2[i] = NULL;
            if (!(env2[i] = ft_strdup(fix->env[j])))
                return (ft_free_tab(env2, i));
            i++;
        }
        j++;

    }
    env2[i] = NULL;
    ft_free_tab(fix->env, ft_env_len(fix) - 1);
    return (env2);
}

char **ft_replace_env(t_fix *fix, char *arg, int egal)
{
    char    **env2;
    int i;
    int j;

    env2 = NULL;
    if (!(env2 = malloc(sizeof(char **) * (ft_env_compare(fix, arg, egal) + 2))))
    {
        ft_error(errno);
        return (NULL);
    }
    i = 0;
    j = 0;
    while (fix->env && fix->env[j])
    {
        if (ft_strncmp(fix->env[j], arg, egal) == 0 && (fix->env[j][egal] == '=' || fix->env[j][egal] == '\0'))
            i--;
        else
        {
            env2[i] = NULL;
            if (!(env2[i] = ft_strdup(fix->env[j])))
            {
                ft_error(errno);
                return (ft_free_tab(env2, i));
            }
        }
        i++;
        j++;
    }
    if (!(env2[i] = ft_strdup(arg)))
    {
        ft_error(errno);
        return (ft_free_tab(env2, i));
    }
    env2[i + 1] = NULL;
    ft_free_tab(fix->env, ft_env_len(fix) - 1);
    return (env2);
}

int ft_export_without_arg(t_fix *fix, int fd)
{
    int i;
    int j;
    char    *sub;

    i = 0;
    while (fix->env && fix->env[i])
    {
        j = 0;
        while (fix->env[i][j] != '=' && fix->env[i][j] != '\0')
        {
         //   ft_putchar_fd(fix->env[i][j], fd);
            j++;
        }
        sub = ft_substr(fix->env[i], 0, j);
        if (ft_strcmp(sub, "_"))
        {
            ft_putstr_fd("declare -x ", fd);
            ft_putstr_fd(sub, fd);
            if (ft_strchr(fix->env[i], '='))
            {
                ft_putchar_fd(fix->env[i][j++], fd);
                ft_putchar_fd('\"', fd);
                while (fix->env[i][j])
                {
                    ft_putchar_fd(fix->env[i][j], fd);
                    j++;
                }
                ft_putstr_fd("\"", fd);
                ft_putstr_fd("\n", fd);
            }
        }
        free(sub);
        i++;
    }
    return (1);
}

int ft_export_check_id(char *arg, int j, t_fix *fix)
{
    int i;
    if (j == 0)
        return (ft_export_err(arg, fix));
    if (ft_isdigit(arg[i]))
        return (ft_export_err(arg, fix));
    i = 0;
    while (i < j)
    {
        if (!(ft_isalnum(arg[i])) && arg[i] != '_')
            return (ft_export_err(arg, fix));
        i++;
    }
    return (1);
}

int ft_export_err(char *arg, t_fix *fix)
{
    ft_putstr_fd("bash: export: \'", 2);
    ft_putstr_fd(arg, 2);
    ft_putstr_fd("\': not a valid identifier\n", 2);
    fix->error = 1;
    return (0);
}

int ft_env_err(t_command *c, t_fix *fix)
{
    if (c->arg[1] && ft_strcmp(c->arg[1], "=") && ft_strcmp(c->arg[1], "-"))
    {
        ft_putstr_fd("env: \"", 2);
        ft_putstr_fd(c->arg[1], 2);
        ft_putstr_fd("\": No such file or directory\n", 2);
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

char **ft_realloc_env(t_fix *fix, char buf[PATH_MAX])
{
    int j;
    char    **env2;

    j = 0;
    while (fix->env && fix->env[j])
        j++;
    if (!(env2 = malloc(sizeof(char **) * (j + 1))))
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
    ft_free_tab(fix->env, ft_env_len(fix) - 1);
    return (env2);
}

int		ft_isnum(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!(str[i] == 45 || (str[i] >= 48 && str[i] <= 57)))
            return (0);
        i++;
    }	
	return (1);
}