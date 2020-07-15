/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:58:36 by aduchemi          #+#    #+#             */
/*   Updated: 2019/10/17 12:41:44 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	length_dst;
	unsigned int	length_src;
	unsigned int	i;

	length_dst = ft_strlen((const char *)dst);
	length_src = ft_strlen(src);
	if (dstsize <= length_dst)
		length_src += dstsize;
	else
		length_src += length_dst;
	i = 0;
	while (src[i] && length_dst + 1 < dstsize)
	{
		dst[length_dst] = src[i];
		length_dst++;
		i++;
	}
	dst[length_dst] = 0;
	return (length_src);
}
