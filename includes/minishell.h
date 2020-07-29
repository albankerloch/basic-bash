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
  int   out;
  char  *n_out;
}       t_command;

void ft_parser(t_command *c, char *line);
int ft_exec(t_command c, char *line);
char *ft_realloc_concat(char *line, char c);
int    ft_redirection_right(t_command *c, char *line, int *i);
int    ft_redirection_left(t_command *c, char *line, int *i);
int    ft_redir_right(t_command *c, char *line, int *i);
int    ft_backslash(char *line, int *i, int *quote);
char	**ft_realloc_arg(char **arg);
void    ft_skip_quotes(char *line, int *i, int *quote);
void    ft_command_construct(t_command *c);
void    ft_command_destroy(t_command *c);
void    ft_touch(t_command *c);
void    ft_redir_echo(t_command *c);

#endif
