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
	while (g_f.env && g_f.env[j])
	{
		if (ft_strncmp(g_f.env[j], arg, egal) == 0 &&
		(g_f.env[j][egal] == '=' || g_f.env[j][egal] == '\0'))
			(*i)--;
		else
		{
			(*env2)[*i] = NULL;
			if (!((*env2)[*i] = ft_strdup(g_f.env[j])))
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
	ft_free_tab(g_f.env, ft_env_len(&g_f) - 1);
	return (env2);
}

char	**ft_realloc_env(t_f *g_f, char buf[PATH_MAX])
{
	int		j;
	char	**env2;

	j = 0;
	while (g_f->env && g_f->env[j])
		j++;
	if (!(env2 = malloc(sizeof(char **) * (j + 1))))
		return (NULL);
	j = 0;
	while (g_f->env && g_f->env[j])
	{
		if (g_f->env[j] && ft_strncmp(g_f->env[j], "PWD",
		ft_strlen("PWD")) == 0)
		{
			if (!(env2[j] = ft_strjoin("PWD=", buf)))
				return (ft_free_tab(env2, j));
		}
		else if (!(env2[j] = ft_strdup(g_f->env[j])))
			return (ft_free_tab(env2, j));
		j++;
	}
	env2[j] = NULL;
	ft_free_tab(g_f->env, ft_env_len(g_f) - 1);
	return (env2);
}
