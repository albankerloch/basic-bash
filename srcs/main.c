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

int		ft_parse_line(char *line, t_f *g_f, int *i)
{
	t_list	*t;
	int		ret;

	if (!(t = ft_init_list()))
		return (0);
	if (!(ret = ft_parser(t, line, i)))
	{
		ft_lstclear(&t, &ft_del_command);
		return (0);
	}
	else if (ret == 1)
	{
		if (!(ft_exec(t, line, g_f)))
		{
			ft_lstclear(&t, &ft_del_command);
			if (g_f->exit >= 0)
				ft_exit(g_f, line, g_f->exit);
			else
				return (0);
		}
	}
	ft_lstclear(&t, &ft_del_command);
	return (1);
}

int		ft_parser_exec(char *line, t_f *g_f)
{
	char	c[2];
	int		i;

	c[0] = '\0';
	c[1] = '\0';
	i = 0;
	if (!line[0])
		return (-1);
	if (!(ft_global_parse(line, c)))
		return (ft_syntax_error(c));
	while (line[i])
	{
		signal(SIGINT, ft_sig_handler);
		signal(SIGQUIT, SIG_IGN);
		if (!(ft_parse_line(line, g_f, &i)))
			return (0);
	}
	return (1);
}

int		main(int argc, char *argv[], char *envp[])
{
	int		ret;

	ft_f_construct(&g_f, envp, argc, argv);
	ret = 1;
	while (1)
	{
		signal(SIGINT, ft_sig_handler);
		signal(SIGQUIT, ft_sig_handler);
		ft_putstr("<minishell> ");
		ret = get_next_line(0, &g_f.line);
		if (ret == 0)
		{
			ft_putstr("\nexit\n");
			ft_exit(&g_f, g_f.line, g_f.error);
		}
		if (ret == -1)
			ft_exit(&g_f, g_f.line, EXIT_FAILURE);
		if (!(ft_parser_exec(g_f.line, &g_f)))
			ft_exit(&g_f, g_f.line, EXIT_FAILURE);
		free(g_f.line);
	}
	return (0);
}
