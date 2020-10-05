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
	t_list *t;
	int	ret;
	int	ret2;

	ft_fix_construct(&fix, envp);
	ret = 1;
	line = NULL;
	while (1)
	{
		t = ft_init_list(&fix);
		signal(SIGINT, ft_sig_handler);
		signal(SIGQUIT, SIG_IGN);
		if (ret == 1)
			ft_putstr("<minishell> ");
		ret = get_next_line(0, &line);
		if (ret == 0)
		{
			ft_putstr("exit Ctrl+D\n");
			ft_exit(&fix, t, line, EXIT_SUCCESS);
		}
		if (ret == -1)
			ft_exit(&fix, t, line, EXIT_FAILURE);
		if (!((ret2 = ft_parser(t, line, &fix))))
			ft_exit(&fix, t, line, EXIT_FAILURE);
		if (ret2 != -1)
		{
			if (!(ft_exec(t, line, &fix)))
			{
				if (fix.exit >= 0)
					ft_exit(&fix, t, line, fix.exit);
				else
					ft_exit(&fix, t, line, EXIT_FAILURE);
			}
		}
		free(line);
		ft_lstclear(&t, &ft_del_command);
	}
	ft_exit_fix(&fix, -2, EXIT_SUCCESS);
	return (0);
}
