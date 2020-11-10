/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:12:34 by aduchemi          #+#    #+#             */
/*   Updated: 2020/11/10 14:41:26 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin_free(char *s, char const *s2)
{
	char	*new;

	if (!(new = ft_strjoin(s, s2)))
		return (NULL);
	free(s);
	return (new);
}

char	*ft_substr_strjoin(char const *s, unsigned int start,
		size_t len, char const *s2)
{
	char	*temp;
	char	*new;

	if (!(temp = ft_substr(s, start, len)))
		return (NULL);
	if (!(new = ft_strjoin(temp, s2)))
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (new);
}

int		ft_len_sub_parse(char *line, int *quote, int *needle)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	while (line[*needle + i] && line[*needle + i] != ';' &&
	line[*needle + i] != '|' && line[*needle + i] != '<' &&
	line[*needle + i] != '>')
	{
		ft_skip_quotes(line, needle + i, quote);
		ft_close_quotes(line, needle + i, quote);
		(*needle)++;
	}
	if (*needle == 0 && (line[*needle + i] == '>' || line[*needle + i] == '<'))
		return (2);
	if (line[*needle + i] == '>' && line[*needle + i + 1] &&
	line[*needle + i + 1] == '>')
		(*needle)++;
	return (1);
}

int		ft_sub_parse(char *line, int i, int needle, char *c)
{
	char	*sub;
	int		ret;

	sub = ft_substr(line, i, needle - i + 1);
	ret = ft_cmd_parse(sub, c);
	free(sub);
	sub = NULL;
	if (ret == 0)
		return (0);
	return (1);
}

int		ft_cmd_parse(char *sub, char *c)
{
	int		i;
	int		j;

	j = 0;
	while (sub[j] == ' ')
		j++;
	i = 0;
	while (sub[i + j])
	{
		if (sub[i + j] == ';' || sub[i + j] == '|' ||
		sub[i + j] == '>' || sub[i + j] == '<')
		{
			if (i == 0)
			{
				c[0] = sub[i + j];
				return (0);
			}
		}
		i++;
	}
	return (1);
}
