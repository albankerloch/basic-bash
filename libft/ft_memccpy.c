/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 12:57:03 by aduchemi          #+#    #+#             */
/*   Updated: 2019/10/15 13:55:09 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;

	i = 0;
	while (n > 0)
	{
		((char *)dst)[i] = ((char *)src)[i];
		if (((char *)src)[i] == (char)c)
			return (&dst[i + 1]);
		n--;
		i++;
	}
	return (NULL);
}
