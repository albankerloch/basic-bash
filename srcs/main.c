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
	t_fix	fix;
	char *line;
    t_command   *c;
	t_list *t;
	int	ret;

	ft_fix_construct(&fix, envp);
	ret = 1;
	line = NULL;
	while (1)
	{
		t = ft_lstnew(ft_command_construct());
		signal(SIGINT, ft_sig_handler);
		signal(SIGQUIT, SIG_IGN);
		if (ret == 1)
			ft_putstr("<minishell> ");
		ret = get_next_line(0, &line);
		if (!ret)
		{
			free(line);
			ft_exit_fix(&fix, -2, EXIT_SUCCESS);
		}
		if (!ft_parser(t, line, &fix))
			ft_exec(t, line, &fix);
		free(line);
		ft_del_command(t->content);
		free(t);
	//	ft_lstclear(&t, &ft_del_command);
	//	ft_lstclear(&t, &ft_command_destroy);
	}
	return (0);
}
