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
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>

typedef struct s_command
{
	char **arg;
  int   input;
  char  *n_input;
  int   add;
  int   quote;
  int   env;
  char  *n_out;
}       t_command;

int ft_parser(t_list *t, char *line, char ***env);
void ft_exec(t_list *t, char *line, char ***envp);
char    *ft_env_var(char *arg, char ***env);

char *ft_realloc_concat(char *line, char c);
int    ft_redirection_right(t_command *c, char *line, int *i, int *k);
int    ft_redirection_left(t_command *c, char *line, int *i, int *k);
int    ft_redir_right(t_command *c, char *line, int *i, int *k);
int    ft_backslash(char *line, int *i, int *quote);
char	**ft_realloc_arg(char **arg);
void    ft_skip_quotes(char *line, int *i, int *quote);
t_command *    ft_command_construct();
void    ft_command_destroy(void *c);
void    ft_touch(t_command *c);
int     ft_checkfile(t_command *c);
int    ft_redir(t_command *c);
int ft_exec_cmd(t_list *t, t_command *c, char *line, char ***envp);
void fork_exec_cmd(t_list *t, t_command *c, char *line, char ***envp);
int    ft_relative_path(t_command *c, char **envp);
int ft_name(char **arg, t_command *c, char *line, int *i);
void    ft_env_destroy(char **env);

#endif
