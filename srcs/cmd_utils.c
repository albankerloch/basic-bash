/**
* @file cmd_utils.c
* @author alban kerloc'h
* @date 11/10/2019
* @version 1.0
*/

#include "../includes/minishell.h"

void	ft_strjoin_buff(char s1[PATH_MAX], char s2[PATH_MAX])
{
	int		i;
	int		j;

	i = 0;
	while (s1[i])
	{
		i++;
	}
	j = 0;
	while (s2[j])
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	s1[i] = 0;
}

void	ft_realloc_concat_buff(char line[PATH_MAX], char c)
{
	line[ft_strlen(line)] = c;
	line[ft_strlen(line) + 1] = '\0';
}
