/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:24:18 by aduchemi          #+#    #+#             */
/*   Updated: 2020/07/15 16:59:40 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char *line;
    t_command   *c;
	t_list *t;
	char **env;
	int	len;
	int	ret;

	len = 0;
	while (envp && envp[len])
		len++;
	env = malloc(sizeof(char **) * len + 1);
	len = 0;
	while (envp && envp[len])
	{
		env[len] = ft_strdup(envp[len]);
		len++;
	}
	env[len] = NULL;

	ret = 1;
	line = NULL;
	while (1)
	{
		if (ret == 1)
			ft_putstr("<minishell> ");
		ret = get_next_line(0, &line);
		t = ft_lstnew(ft_command_construct());
		if (!ft_parser(t, line, &env))
			ft_exec(t, line, &env);
	/*	int j = 0;
        while (env && env[j])
        {
            if (env[j] && ft_strncmp(env[j], "PWD", ft_strlen("PWD")) == 0)
            {
				ft_putstr(env[j]);
            	ft_putchar('\n');
			}
            j++;
        }*/

	//	ft_lstclear(&t, &ft_command_destroy);
	}
	//ft_env_destroy(env); //utilité ??
	return (0);
}
