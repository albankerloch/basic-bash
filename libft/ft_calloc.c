/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:12:05 by aduchemi          #+#    #+#             */
/*   Updated: 2019/10/21 17:20:14 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*dest;
	size_t	i;

	if (!(dest = malloc(size * count)))
		return (NULL);
	i = 0;
	while (i < count)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
