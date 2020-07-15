/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:27:23 by aduchemi          #+#    #+#             */
/*   Updated: 2020/01/02 10:47:59 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(size_t count, char *line, int car)
{
	char	*new;

	if (!(new = malloc(sizeof(*new) * (count + car + 1))))
		return (NULL);
	new[count + car] = '\0';
	if (car > 0)
		ft_memcpy(new, line, car);
	free(line);
	return (new);
}

int		ft_get_2_squeeze(char *buf, char **line, int *i, int *lus)
{
	int		temp;
	int		car;

	temp = *i;
	car = ft_strlen(*line);
	while (buf[*i] != '\n' && buf[*i] != '\0')
		*i = *i + 1;
	if ((*line = ft_realloc((*i - temp), *line, car)) == NULL)
		return (-1);
	while (temp < *i)
	{
		(*line)[car] = buf[temp];
		temp++;
		car++;
		*lus = *lus - 1;
	}
	if (buf[*i] == '\n')
	{
		*lus = *lus - 1;
		*i = *i + 1;
		return (1);
	}
	return (0);
}
