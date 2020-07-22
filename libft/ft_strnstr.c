/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:30:18 by aduchemi          #+#    #+#             */
/*   Updated: 2019/10/18 16:48:57 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int				needle_length;
	unsigned long	i;
	unsigned long	j;

	needle_length = 0;
	while (needle[needle_length])
		needle_length++;
	if (needle_length == 0)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && (i <= len))
	{
		j = 0;
		while ((haystack[i + j] == needle[j]) && ((i + j) < len))
		{
			j++;
			if (needle[j] == 0)
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}
