/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:36:28 by aduchemi          #+#    #+#             */
/*   Updated: 2020/11/07 14:14:22 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_unset_env(t_f *g_f, char *arg)
{
	char	**env2;
	int		i;
	int		j;

	env2 = NULL;
	if (!(env2 = malloc(sizeof(char **) * ft_env_len(g_f))))
		return (NULL);
	i = 0;
	j = 0;
	while (g_f->env && g_f->env[j])
	{
		if (!(ft_strncmp(g_f->env[j], arg, ft_strlen(arg)) == 0))
		{
			env2[i] = NULL;
			if (!(env2[i] = ft_strdup(g_f->env[j])))
				return (ft_free_tab(env2, i));
			i++;
		}
		j++;
	}
	env2[i] = NULL;
	ft_free_tab(g_f->env, ft_env_len(g_f) - 1);
	return (env2);
}

void	ft_aff_export_without_arg(int i, int *j, int fd)
{
	char	*sub;

	sub = ft_substr(g_f.env[i], 0, *j);
	if (ft_strcmp(sub, "_"))
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(sub, fd);
		if (ft_strchr(g_f.env[i], '='))
		{
			ft_putchar_fd(g_f.env[i][(*j)++], fd);
			ft_putchar_fd('\"', fd);
			while (g_f.env[i][*j])
			{
				ft_putchar_fd(g_f.env[i][*j], fd);
				(*j)++;
			}
			ft_putstr_fd("\"", fd);
		}
		ft_putstr_fd("\n", fd);
	}
	free(sub);
}

int		ft_export_without_arg(t_f *g_f, int fd)
{
	int		i;
	int		j;

	i = 0;
	while (g_f->env && g_f->env[i])
	{
		j = 0;
		while (g_f->env[i][j] != '=' && g_f->env[i][j] != '\0')
			j++;
		ft_aff_export_without_arg(i, &j, fd);
		i++;
	}
	return (1);
}

int		ft_export_check_id(char *arg, int j)
{
	int		i;

	if (j == 0)
		return (ft_export_err(arg));
	i = 0;
	if (!(ft_isalpha(arg[i])) && arg[i] != '_')
		return (ft_export_err(arg));
	while (i < j)
	{
		if (!(ft_isalnum(arg[i])) && arg[i] != '_')
			return (ft_export_err(arg));
		i++;
	}
	return (1);
}

int		ft_export_err(char *arg)
{
	ft_putstr_fd("bash: export: \'", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	g_f.error = 1;
	return (0);
}
