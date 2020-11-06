#include "../includes/minishell.h"

char *ft_strjoin_free(char *s, char const *s2)
{
    char *new;

    if (!(new = ft_strjoin(s, s2)))
    {
        return (NULL);
    }
    free(s);
    return (new);
}

char *ft_substr_strjoin(char const *s, unsigned int start, size_t len, char const *s2)
{
    char *temp;
    char *new;

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

int ft_realloc_fix_error(char **arg, t_fix *fix)
{
	if (fix->error >= 100)
	{
		if(!(*arg = ft_realloc_concat(*arg, fix->error / 100 + 48)))
			return (0);
	}
	if (fix->error >= 10)
	{
		if(!(*arg = ft_realloc_concat(*arg, fix->error % 100 / 10 + 48)))
			return (0);
	}
	if(!(*arg = ft_realloc_concat(*arg, fix->error % 10 + 48)))
        return (0);   
    return (1);
}

int ft_realloc_var(char **arg, char *line, int *i, t_fix *fix)
{
    int j;
    int k;

    j = 0;
    while (line[*i + j] && (ft_isalnum(line[*i + j]) || line[*i + j] == '_'))
        j++;
    k = 0;
    while (fix->env && fix->env[k])
    {
		if (ft_strncmp(fix->env[k], &line[*i], j) == 0 && fix->env[k][j] == '=')
        {
			*i = *i + j - 1;
			j++;
			if(!(*arg = ft_strjoin_free(*arg, &(fix->env[k][j]))))
                return (0);
			return (1);
		} 
		k++;
	}
	*i = *i + j - 1;
    return (2);
}

char	*ft_realloc_concat(char *line, char c)
{
	char	*new;

	if (!(new = malloc(sizeof(*new) * (ft_strlen(line) + 2))))
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

void	ft_error(int err)
{
	ft_putstr_fd("Error : ", 2);
	ft_putnbr_fd(errno, 2);
	ft_putchar_fd(' ', 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
}

int    ft_syntax_error(char *s)
{
    ft_putstr_fd("bash: syntax error near unexpected token \" ", 2);
    ft_putstr_fd(s, 2);
    ft_putstr_fd(" \"\n", 2);
    fix.error = 2;
    return (2);
}

int		ft_global_parse(char *line, char *c)
{
	int	i;
	int	quote;
	int	needle;
	char	*sub;
	int	ret;

	quote = 0;
	i = 0;
	sub = NULL;
	needle = 0;
	while (line[i])
	{
		while (line[needle] && line[needle] != ';' && line[needle] != '|')
		{
			ft_skip_quotes(line, &needle, &quote);
			ft_close_quotes(line, &needle, &quote);
			needle++;
		}
		//printf("needle=%d |%c| quote=%d\n", needle, line[needle], quote);
		if (quote == 0)
		{
			sub = ft_substr(line, i, needle - i + 1);
		//	printf("sub=|%s| start=%d len=%d quote=%d\n", sub, i, needle - i + 1, quote);
			ret = ft_cmd_parse(sub, c);
			free(sub);
			sub = NULL;
			if (ret == 0)
				return (0);
		}
		needle++;
		i = needle;
	}
	return (1);
}

int	ft_cmd_parse(char *sub, char *c)
{
	int	i;
	int	j;

	j = 0;
	while (sub[j] == ' ')
		j++;
	i = 0;
	while (sub[i + j])
	{
		if (sub[i + j] == ';' || sub[i + j] == '|')
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