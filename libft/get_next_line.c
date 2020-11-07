/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:38:39 by aduchemi          #+#    #+#             */
/*   Updated: 2020/01/02 10:52:16 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_next_line(int fd, char **line)
{
	static int	i;
	int			temp;
	static int	lus;
	static char	buf[BUFFER_SIZE + 1];

	if (!(*line = malloc(sizeof(char *))))
		return (-1);
	(*line)[0] = '\0';
	while (i == 0 || lus >= 0)
	{
		if (i == 0 || lus == 0)
		{
			if ((lus = read(fd, buf, BUFFER_SIZE)) == -1)
				return (-1);
			buf[lus] = '\0';
			i = 0;
		}
		if (lus == 0 && (*line)[0] == '\0')
			return (0);
		if ((temp = ft_get_2_squeeze(buf, line, &i, &lus)) == -1)
			return (-1);
		else if (temp == 1)
			return (1);
	}
	return (-1);
}
