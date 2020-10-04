#include "../includes/minishell.h"

t_list *ft_add_list(t_list *t, t_fix *fix)
{
    t_command   *c;

    if(!(c = ft_command_construct()))
    {
        ft_lstclear(&t, &ft_del_command);
		ft_exit_fix(fix, -2, EXIT_FAILURE);
    }
	if(!(t = ft_lstnew(c)))
	{
		ft_free_command(c);
		ft_lstclear(&t, &ft_del_command);
		ft_exit_fix(fix, -2, EXIT_FAILURE);
	}
    return(t);
}

t_list *ft_init_list(t_fix *fix)
{
    t_list *t;
    t_command   *c;

    if(!(c = ft_command_construct()))
		ft_exit_fix(fix, -2, EXIT_FAILURE);
	if(!(t = ft_lstnew(c)))
	{
		ft_free_command(c);
		free(t);
		ft_exit_fix(fix, -2, EXIT_FAILURE);
	}
    return(t);
}

t_command *ft_command_construct()
{
    t_command *c;

    c = malloc(sizeof(t_command));
    c->input = 0;
    c->n_input = malloc(1);
    c->n_input[0] = '\0';
    c->add = 0;
    c->quote = 0;
    c->n_out = malloc(1);
    c->n_out[0] = '\0';
    c->arg = malloc(sizeof(char*) * 2);
    c->arg[0] = malloc(1);
    c->arg[0][0] = '\0';
    c->arg[1] = NULL;
    return(c);
}

void   ft_fix_construct(t_fix *fix, char **envp)
{
	int	len;
    
    len = 0;
	while (envp && envp[len])
		len++;
	if(!(fix->env = malloc(sizeof(char **) * len + 1)))
        ft_exit_fix(fix, -1, EXIT_FAILURE);
    len = 0;
	while (envp && envp[len])
	{
		if(!(fix->env[len] = ft_strdup(envp[len])))
            ft_exit_fix(fix, len, EXIT_FAILURE);
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