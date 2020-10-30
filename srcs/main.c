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

int ft_parser_exec(char *line, t_fix *fix)
{
	t_list *t;
    int    i;
	int	ret;

	i = 0;
    if (!line[0])
        return (-1);
	while(line[i])
    {
		signal(SIGINT, ft_sig_handler);
		signal(SIGQUIT, SIG_IGN);
		if (!(t = ft_init_list(fix)))
			return (0);
		if (!(ret = ft_parser(t, line, fix, &i)))
		{
			ft_lstclear(&t, &ft_del_command);
			return (0);
		}
		else if (ret == 1)
		{
			if (!(ft_exec(t, line, fix)))
			{
				ft_lstclear(&t, &ft_del_command);
				if (fix->exit >= 0)
					ft_exit(fix, line, fix->exit);
				else
					return (0);
			}
		}
		ft_lstclear(&t, &ft_del_command);
	}
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_fix	fix;
	char *line;
	int	ret;
	int	parsing;

	ft_fix_construct(&fix, envp);
	ret = 1;
	line = NULL;
	while (1)
	{
		signal(SIGINT, ft_sig_handler);
		signal(SIGQUIT, SIG_IGN);
	//	ft_putstr("<minishell> ");
		ret = get_next_line(0, &line);
		if (ret == 0)
		{
	//		ft_putstr("\nexit\n");
			ft_exit(&fix, line, EXIT_SUCCESS);
		}
		if (ret == -1)
			ft_exit(&fix, line, EXIT_FAILURE);
		if (!(ft_parser_exec(line, &fix)))
			ft_exit(&fix, line, EXIT_FAILURE);
		free(line);
	//	printf("fix->error=%d fix->exit=%d\n", fix.error, fix.exit);
	}
	return (0);
}