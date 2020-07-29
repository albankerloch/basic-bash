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

int	main()
{
	char *line;
    t_command   *c;
	t_list *t;

	line = NULL;
	while (1)
	{
		//prompt
		ft_putstr("<minishell> ");
		get_next_line(0, &line);
		//c = ft_command_construct();
		t = ft_lstnew(ft_command_construct());
		if (!ft_parser(t, line))
			ft_exec(t, line);
	//	ft_command_destroy(&c);
	}
	return (0);
}
