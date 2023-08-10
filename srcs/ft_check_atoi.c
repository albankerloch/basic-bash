/**
* @file ft_check_atoi.c
* @author alban kerloc'h
* @date 11/10/2019
* @version 1.0
*/

#include "../includes/minishell.h"

int		ft_check_atoi(const char *str)
{
	int					i;
	int					signe;
	unsigned long long	nb;

	i = 0;
	nb = 0;
	signe = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' ||
			str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		signe = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - 48;
		i++;
	}
	if ((nb > LLONG_MAX && signe == 1) || (nb - 1 > LLONG_MAX && signe == -1))
		return (0);
	return (1);
}
