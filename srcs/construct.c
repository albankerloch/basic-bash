#include "../includes/minishell.h"

t_command *ft_command_construct()
{
    t_command *c;

    c = malloc(sizeof(t_command));
    c->input = 0;
    c->n_input = malloc(1);
    c->n_input[0] = '\0';
    c->add = 0;
    c->quote = 0;
    c->env = 0;
    c->n_out = malloc(1);
    c->n_out[0] = '\0';
    c->arg = malloc(sizeof(char*));
    c->arg[0] = malloc(1);
    c->arg[0][0] = '\0';
    return(c);
}

void   ft_fix_construct(t_fix *fix, char **envp)
{
	int	len;
    
    /*if(!(*fix = malloc(sizeof(t_fix))))
    {
        free(*fix);
        //exit(EXIT_FAILURE);
    }*/
    len = 0;
	while (envp && envp[len])
		len++;
	if(!(fix->env = malloc(sizeof(char **) * len + 1)))
        ft_exit_fix(fix, -1);
    len = 0;
	while (envp && envp[len])
	{
		if(!(fix->env[len] = ft_strdup(envp[len])))
            ft_exit_fix(fix, len);
		len++;
	}
	fix->env[len] = NULL;
    fix->error = 1;
}

void    ft_command_destroy(void *c)
{
    int     i;
    t_command *c_bis;
    
    c_bis = c;
    i = 0;
    free(c_bis->n_input);
    free(c_bis->n_out);
    while (c_bis->arg[i])
    {
        free(c_bis->arg[i]);
        i++;
    }
    free(c_bis->arg);
    free(c_bis);
}

void    ft_env_destroy(char **env)
{
    int i;

    i = 0;
    while (env && env[i])
    {
        free(env[i]);
        i++;
    }
    free(env);
}