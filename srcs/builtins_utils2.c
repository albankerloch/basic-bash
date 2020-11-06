/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:36:28 by aduchemi          #+#    #+#             */
/*   Updated: 2020/11/06 22:36:30 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
            j++;
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
