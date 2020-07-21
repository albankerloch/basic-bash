/*best parser ever*/

#include "../includes/minishell.h"

t_command ft_parser(char *line)
{
    t_command   c;
    int         i;

 //   c.k_begin = 0;
    i = 0;
c.arg = malloc(1);
	
    
    while(line[i])
    {
    	c.arg = ft_realloc_concat(c.arg, line[i]);
        i++;
	}
 //   c.k_end = i;
   // c.a_begin = i + 1;
   /* while(line[i] != '\0')
    {
    	//realloc char si diff " ' > space et pas debut d'un redic en debut mot
	// si space realloc une fois (cmp avec malloc en cours arg)
	// si " ', cherche second, realloc ou erreur
	// si redir, chg struct
	
	i++;
	}
	// supprimer space a la fin de arg
    c.a_end = i;*/

 //   printf("%d %d %d %d\n", c.k_begin, c.k_end, c.a_begin, c.a_end);

    return (c);
}
