/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:36:35 by aduchemi          #+#    #+#             */
/*   Updated: 2020/11/07 14:57:02 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_replace_env_dup(char *arg, int egal, char ***env2, int *i)
{
	int		j;

	*i = 0;
	j = 0;
	while (fix.env && fix.env[j])
	{
		if (ft_strncmp(fix.env[j], arg, egal) == 0 &&
		(fix.env[j][egal] == '=' || fix.env[j][egal] == '\0'))
			(*i)--;
		else
		{
			(*env2)[*i] = NULL;
			if (!((*env2)[*i] = ft_strdup(fix.env[j])))
			{
				ft_error(errno);
				ft_free_tab(*env2, *i);
				return (0);
			}
		}
		(*i)++;
		j++;
	}
	return (1);
}

char	**ft_replace_env(char *arg, int egal)
{
	char	**env2;
	int		i;

	env2 = NULL;
	if (!(env2 = malloc(sizeof(char **) *
	(ft_env_compare(arg, egal) + 2))))
	{
		ft_error(errno);
		return (NULL);
	}
	if (!ft_replace_env_dup(arg, egal, &env2, &i))
		return (NULL);
	if (!(env2[i] = ft_strdup(arg)))
	{
		ft_error(errno);
		return (ft_free_tab(env2, i));
	}
	env2[i + 1] = NULL;
	ft_free_tab(fix.env, ft_env_len(&fix) - 1);
	return (env2);
}

char	**ft_realloc_env(t_fix *fix, char buf[PATH_MAX])
{
	int		j;
	char	**env2;

	j = 0;
	while (fix->env && fix->env[j])
		j++;
	if (!(env2 = malloc(sizeof(char **) * (j + 1))))
		return (NULL);
	j = 0;
	while (fix->env && fix->env[j])
	{
		if (fix->env[j] && ft_strncmp(fix->env[j], "PWD",
		ft_strlen("PWD")) == 0)
		{
			if (!(env2[j] = ft_strjoin("PWD=", buf)))
				return (ft_free_tab(env2, j));
		}
		else if (!(env2[j] = ft_strdup(fix->env[j])))
			return (ft_free_tab(env2, j));
		j++;
	}
	env2[j] = NULL;
	ft_free_tab(fix->env, ft_env_len(fix) - 1);
	return (env2);
}
