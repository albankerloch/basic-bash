/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:52:13 by aduchemi          #+#    #+#             */
/*   Updated: 2019/10/16 18:08:41 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_check(char c, char const *set)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*dst;

	if (!(dst = malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		if (!(ft_check(s1[i], set) == 1 && (i == 0 || j == 0)))
		{
			dst[j] = s1[i];
			j++;
		}
		i++;
	}
	dst[j] = 0;
	while (j > 0 && ft_check(dst[j - 1], set) == 1)
	{
		dst[j - 1] = 0;
		j--;
	}
	return (dst);
}
