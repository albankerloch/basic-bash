/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:47:27 by aduchemi          #+#    #+#             */
/*   Updated: 2020/07/21 21:21:49 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct s_command
{
	char **arg;
  int   input;
  char  *n_input;
  int   add;
  int   quote;
  int   simple_quote;
  int   double_quote;
  int   out;
  char  *n_out;
  int   err;
  char  *n_err;
}       t_command;

t_command ft_parser(char *line);
int ft_exec(t_command c, char *line);
char *ft_realloc_concat(char *line, char c);
int    ft_redirection(t_command *c, char *line, int *i);
int    ft_redir_right(t_command *c, char *line, int *i, char output);
int    ft_add(t_command *c, char *line, int *i, char output);
int    ft_simple_quoting(t_command *c, char *line, int *i);
int    ft_double_quoting(t_command *c, char *line, int *i);
int    ft_backslash(t_command *c, char *line, int *i);
void    ft_sub_arg(char **arg, int i);
char	**ft_realloc_arg(char **arg);
int    ft_check_end_quote(t_command *c, char *line, int i, int q);

#endif
