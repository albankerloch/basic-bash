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

	ft_fix_construct(&fix, envp);
	ret = 1;
	line = NULL;
//	while (1)
//	{
		t = ft_init_list(&fix);
/*		signal(SIGINT, ft_sig_handler);
		signal(SIGQUIT, SIG_IGN);
		if (ret == 1)
			ft_putstr("<minishell> ");
		ret = get_next_line(0, &line);
		if (!ret)
		{
			ft_putstr("exit\n");
			exit (0);
		}
		if (!ft_parser(t, line, &fix))
			ft_exec(t, line, &fix);S
	//	ft_lstclear(&t, &ft_command_destroy);
	}
	//ft_env_destroy(env); //utilité ??*/
	ft_free_command(t->content);
	free(t);
	ft_exit_fix(&fix, -2);
	return (0);
}
