#include "../includes/minishell.h"

char	*ft_realloc_concat(char *line, char c)
{
	char	*new;
//	printf("char c =%c %d\n", c, c);
	if (!(new = malloc(sizeof(*new) * (ft_strlen(line) + 1))))
		return (NULL);
	if (ft_strlen(line) > 0)
		ft_memcpy(new, line, ft_strlen(line));
	new[ft_strlen(line)] = c;
	new[ft_strlen(line) + 1] = '\0';
	free(line);
	return (new);
}

void ft_check(char **new)
{
	int i;
	
	i = 0;
	while (new[i])
    {
        printf("LLL%i\n", i);
        i++;
    }
}

char	**ft_realloc_arg(char **arg)
{
	char	**new;
	int		i;

	i = 0;
	while (arg[i])
		i++;
	if (!(new = malloc(sizeof(char*) * (i + 2))))
		return (NULL);
	i = 0;
	while (arg[i])
	{
		new[i] = ft_strdup(arg[i]);
		free(arg[i]);
		i++;
	}
	new[i] = malloc(1);
	new[i + 1] = NULL;
	free(arg);
	return (new);
}