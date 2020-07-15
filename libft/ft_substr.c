/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 18:06:31 by aduchemi          #+#    #+#             */
/*   Updated: 2020/07/15 18:02:53 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*s2;

	s2 = NULL;
	if (start > ft_strlen(s) || s == NULL)
	{
		if (!(s2 = malloc(1)))
			return (NULL);
		return (s2);
	}
	if (!(s2 = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (s[i] && (i < start))
		i++;
	j = 0;
	while ((j < len) && s[i + j])
	{
		s2[j] = s[i + j];
		j++;
	}
	s2[j] = 0;
	return (s2);
}
