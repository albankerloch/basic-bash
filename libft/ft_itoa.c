/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:01:12 by aduchemi          #+#    #+#             */
/*   Updated: 2019/10/18 18:29:35 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n, int *len)
{
	if (n < 0)
	{
		n = 147483648;
		*len = *len + 2;
	}
	if (n / 10 > 0)
	{
		*len = *len + 1;
		ft_len(n / 10, len);
	}
	return (*len);
}

static char	*ft_convert(int n, char *s, int *i)
{
	if (n > 9)
		ft_convert(n / 10, s, i);
	s[*i] = n % 10 + 48;
	*i = *i + 1;
	s[*i] = 0;
	return (s);
}

static char	*ft_malloc(int n)
{
	int		len;
	char	*s;

	len = 0;
	len = ft_len(n, &len) + 1;
	if (n < 0)
	{
		if (!(s = malloc(sizeof(char) * (len + 2))))
			return (NULL);
	}
	else
	{
		if (!(s = malloc(sizeof(char) * (len + 1))))
			return (NULL);
	}
	return (s);
}

char		*ft_itoa(int n)
{
	int		i;
	char	*s;

	if (!(s = ft_malloc(n)))
		return (NULL);
	if (n == -2147483648)
	{
		s[0] = '-';
		s[1] = '2';
		n = 147483648;
		i = 2;
	}
	else if (n < 0)
	{
		s[0] = '-';
		n *= -1;
		i = 1;
	}
	else
		i = 0;
	s = ft_convert(n, s, &i);
	return (s);
}
