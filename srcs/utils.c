#include "../includes/minishell.h"

char	*ft_realloc_concat(char *line, char c)
{
	char	*new;

	if (!(new = malloc(sizeof(*new) * (ft_strlen(line) + 1))))
		return (NULL);
	if (ft_strlen(line) > 0)
		ft_memcpy(new, line, ft_strlen(line));
	new[ft_strlen(line)] = c;
	new[ft_strlen(line) + 1] = '\0';
	free(line);
	return (new);
}

char	**ft_realloc_arg(char **arg)
{
	char	**new;
	int		i;

	i = 0;
	while (arg[i])
		i++;
//	printf ("--> %d\n", i);
	if (!(new = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
//	printf ("milieu realloc arg\n");
	i = 0;
	while (arg[i])
	{
		new[i] = ft_strdup(arg[i]);
//		printf ("----> %d\n", i);
		free(arg[i]);
		i++;
	}
	new[i] = malloc(1);
	free(arg);
//	printf ("fin realloc arg\n");
	return (new);
}