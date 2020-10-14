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

char **ft_free_tab(char **new, int i)
{
	int k;

	k = 0;
	while (k <= i)
	{
		free(new[k]);
		new[k] = NULL;
		k++;
	}
	free(new);
	new = NULL;
	return (NULL);
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
		if(!(new[i] = ft_strdup(arg[i])))
			return (ft_free_tab(new, i));
		i++;
	}
	if(!(new[i] = malloc(1)))
		return (ft_free_tab(new, i));
	new[i][0] = '\0';
	new[i + 1] = NULL;
	ft_free_tab(arg, i);
	return (new);
}