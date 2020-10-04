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
  char  *n_out;
}       t_command;

typedef struct s_fix
{
  int   error;
  char **env;
}       t_fix;

int     ft_parser(t_list *t, char *line, t_fix *fix);
int     ft_exec(t_list *t, char *line, t_fix *fix);
char    *ft_env_var(char *arg, int h, t_fix *fix);
int     ft_arg_var(char **arg, t_fix *fix);
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
int     ft_open_redir(t_command *c);
int    ft_close_redir(t_command *c, int fd);
int     ft_builtins(t_command *c, char *line, t_fix *fix);
int    fork_exec_cmd(t_command *c, char *line, t_fix *fix);
int     ft_relative_path(t_command *c, t_fix *fix);
int     ft_new_arg(char **arg, t_command *c, char *line, int *i);
void    ft_env_destroy(char **env);
void    ft_sig_handler(int signum);
void    ft_sig_handler_process(int signum);
void    ft_sig_handler_quit(int signum);
int     ft_syntax_export(t_command *c, int fd, t_fix *fix);
int     ft_export_err(int err, int fd, char *arg, t_fix *fix);

int ft_echo(t_command *c, t_fix *fix, int fd);
int ft_env(t_command *c, t_fix *fix, int fd);
int ft_pwd(t_command *c, t_fix *fix, int fd);
int ft_export(t_command *c, t_fix *fix, int fd);
int ft_unset(t_command *c, t_fix *fix, int fd);
int ft_cd(t_command *c, t_fix *fix, int fd);

int     ft_env_len(t_fix *fix);
int     ft_env_compare(t_fix *fix, char *arg, int n);
char    **ft_env_cpy(t_fix *fix, char *arg, int len, int egal);
char    *ft_join_end_var(char *val_var, char *arg, int j);
char    *ft_valeur_variable(t_fix *fix, char *nom_var);
void    ft_echo_n(int *n, char *arg, int *i);


int     ft_exit_fix(t_fix *fix, int i, int e);
void    ft_exit(t_fix *fix, t_list *t, char *line, int e);
t_command  *ft_free_part_command(t_command *c, int i);
void    ft_del_command(void *c);
void    ft_free_command(t_command *c);
t_list  *ft_init_list(t_fix *fix);
int     ft_add_list(t_list *t, t_fix *fix);
char    **ft_free_tab(char **new, int i);
char *ft_substr_strjoin(char const *s, unsigned int start, size_t len, char const *s2);
char *ft_strjoin_substr(char const *s1, char const *s, unsigned int start, size_t len);

#endif
