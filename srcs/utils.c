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
	//printf(" new = |%s|\n", new);
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

static char **ft_realloc_arg_free(char **new, int i)
{
	int k;

	k = 0;
	while (k < i)
	{
		free(new[k]);
		k++;
	}
	free(new);
	return (NULL);
}

char	**ft_realloc_arg(char **arg)
{
	char	**new;
	int		i;
	int		k;

	i = 0;
	while (arg[i])
		i++;
	if (!(new = malloc(sizeof(char*) * (i + 2))))
		return (NULL);
	i = 0;
	while (arg[i])
	{
		if(!(new[i] = ft_strdup(arg[i])))
			return (ft_realloc_arg_free(new, i));
	//	printf("pre free while realloc arg %s i=%d\n", arg[i], i);
		free(arg[i]);
		i++;
	}
	if(!(new[i] = malloc(1)))
		return (ft_realloc_arg_free(new, i));
	new[i][0] = '\0';
	new[i + 1] = NULL;
	free(arg);
	return (new);
}