/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:36:35 by aduchemi          #+#    #+#             */
/*   Updated: 2020/11/06 22:36:37 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char **ft_realloc_env(t_fix *fix, char buf[PATH_MAX])
{
    int     j;
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
