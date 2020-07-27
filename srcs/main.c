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
    t_command   c;

	line = NULL;
	while (1)
	{
		//prompt
		ft_putstr("<minishell> ");
		get_next_line(0, &line);
    	ft_command_construct(&c);
		ft_parser(&c, line);
		ft_exec(c, line);
		ft_command_destroy(&c);
	}
	return (0);
}
