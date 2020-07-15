/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:17:01 by aduchemi          #+#    #+#             */
/*   Updated: 2019/10/18 18:27:53 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_cpy(const char *s, int k, int i)
{
	int		j;
	char	*chaine;

	if (!(chaine = malloc(sizeof(char) * (i - k + 1))))
		return (NULL);
	j = 0;
	while (k < i)
	{
		chaine[j] = s[k];
		k++;
		j++;
	}
	chaine[j] = 0;
	return (chaine);
}

static char	**ft_set_variables(const char *s, int *i, int *j, int *k)
{
	char	**tab;

	if (!(tab = malloc(sizeof(*tab) * (ft_strlen((char *)s) + 1))))
		return (NULL);
	*i = 0;
	*j = 0;
	*k = 0;
	return (tab);
}

char		**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	if (!(tab = ft_set_variables(s, &i, &j, &k)))
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i])
		{
			i++;
			k = i;
		}
		while (s[i] != c && s[i])
			i++;
		if (i != k)
		{
			if (!(tab[j] = ft_cpy(s, k, i)))
				return (NULL);
			j++;
		}
	}
	tab[j] = 0;
	return (tab);
}
