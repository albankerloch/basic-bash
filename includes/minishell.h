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
# include <signal.h>

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

typedef struct s_fix
{
  int   error;
  char **env;
}       t_fix;

int     ft_parser(t_list *t, char *line, t_fix *fix);
void    ft_exec(t_list *t, char *line, t_fix *fix);
char    *ft_env_var(char *arg, t_fix *fix);
void    ft_fix_construct(t_fix *fix, char **envp);
char    *ft_realloc_concat(char *line, char c);
int     ft_redirection_right(t_command *c, char *line, int *i, int *k);
int     ft_redirection_left(t_command *c, char *line, int *i, int *k);
int     ft_redir_right(t_command *c, char *line, int *i, int *k);
int     ft_backslash(char *line, int *i, int *quote);
char	  **ft_realloc_arg(char **arg);
void    ft_skip_quotes(char *line, int *i, int *quote);
t_command *    ft_command_construct();
void    ft_command_destroy(void *c);
void    ft_touch(t_command *c);
int     ft_checkfile(t_command *c);
int     ft_redir(t_command *c);
int     ft_exec_cmd(t_command *c, char *line, t_fix *fix);
void    fork_exec_cmd(t_command *c, char *line, t_fix *fix);
int     ft_relative_path(t_command *c, t_fix *fix);
int     ft_name(char **arg, t_command *c, char *line, int *i);
void    ft_env_destroy(char **env);
void    ft_sig_handler(int signum);
void    ft_sig_handler_process(int signum);
void    ft_sig_handler_quit(int signum);
void    ft_exit_fix(t_fix *fix, int i, int e);
void    ft_free_command(t_command *c);
t_command  *ft_free_part_command(t_command *c, int i);
t_list  *ft_init_list(t_fix *fix);
t_list  *ft_add_list(t_list *t, t_fix *fix);
void    ft_del_command(void *c);
void    ft_exit(t_fix *fix, t_list *t, char *line, int e);

#endif
