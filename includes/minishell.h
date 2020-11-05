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
# include <stdio.h>///à supprimer
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <signal.h>
# include <errno.h>
# include <string.h>

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
  int   exit;
  char **env;
}       t_fix;

int     ft_parser_exec(char *line, t_fix *fix);
int     ft_parser(t_list *t, char *line, t_fix *fix, int *i);
int     ft_exec(t_list *t, char *line, t_fix *fix);
char    *ft_env_var(char *arg, int h, t_fix *fix);
int     ft_arg_var(char **arg, t_fix *fix);
void    ft_fix_construct(t_fix *fix, char **envp);
char    *ft_realloc_concat(char *line, char c);
int     ft_redirection_right(t_command *c, char *line, int *i, t_fix *fix);
int     ft_redirection_left(t_command *c, char *line, int *i, t_fix *fix);
int     ft_redir_right(t_command *c, char *line, int *i, t_fix *fix);
int     ft_backslash(char *line, int *i, int *quote);
char	  **ft_realloc_arg(char **arg);
void    ft_skip_quotes(char *line, int *i, int *quote);
t_command *    ft_command_construct();
void    ft_command_destroy(void *c);
int    ft_touch(t_command *c);
int     ft_checkfile(t_command *c, t_fix *fix);
int     ft_open_redir(t_command *c);
int     ft_builtins(t_command *c, char *line, t_fix *fix, int fd);
int     fork_exec_cmd(t_command *c, char *line, t_fix *fix);
int     ft_relative_path(t_command *c, t_fix *fix);
int     ft_new_arg(t_command *c, char *line, int *i, t_fix *fix);
void    ft_env_destroy(char **env);
void    ft_sig_handler(int signum);
void    ft_sig_handler_process(int signum);
void    ft_sig_handler_quit(int signum);
int     ft_syntax_export(t_command *c, int fd, t_fix *fix);
int     ft_export_without_arg(t_fix *fix, int fd);
int     ft_export_err(char *arg, t_fix *fix);
int     ft_env_err(t_command *c, t_fix *fix);
void    ft_execve(t_command *c, t_fix *fix);
char    **ft_realloc_env(t_fix *fix, char buf[PATH_MAX]);
void    ft_strjoin_buff(char s1[PATH_MAX], char s2[PATH_MAX]);
void    ft_realloc_concat_buff(char line[PATH_MAX], char c);
void	ft_error(int err);

int ft_echo(t_command *c, t_fix *fix, int fd);
int ft_env(t_command *c, t_fix *fix, int fd);
int ft_pwd(t_command *c, t_fix *fix, int fd);
int ft_export(t_command *c, t_fix *fix, int fd);
int ft_unset(t_command *c, t_fix *fix, int fd);
int ft_cd(t_command *c, t_fix *fix, int fd);
int ft_builtin_exit(t_command *c, t_fix *fix, int fd);

int     ft_env_len(t_fix *fix);
char    **ft_replace_env(t_fix *fix, char *arg, int egal);
char    *ft_join_end_var(char *val_var, char *arg, int j);
char    *ft_valeur_variable(t_fix *fix, char *nom_var);
void    ft_echo_n(int *n, char **arg, int *i);


int     ft_exit_fix(t_fix *fix, int i, int e);
void    ft_exit(t_fix *fix, char *line, int e);
t_command  *ft_free_part_command(t_command *c, int i);
void    ft_del_command(void *c);
void    ft_free_command(t_command *c);
t_list  *ft_init_list(t_fix *fix);
int     ft_add_list(t_list *t, t_fix *fix);
char    **ft_free_tab(char **new, int i);
char    *ft_substr_strjoin(char const *s, unsigned int start, size_t len, char const *s2);
char    *ft_strjoin_substr(char const *s1, char const *s, unsigned int start, size_t len);
int			ft_atoi(const char *str);
int		  ft_isnum(char *str);

char    **ft_env_cpy(t_fix *fix, char *arg, int len, int egal);
int     ft_env_compare(t_fix *fix, char *arg, int n);
int     ft_export_check_id(char *arg, int i, t_fix *fix);
char    **ft_unset_env(t_fix *fix, char *arg);
int     ft_realloc_var(char **arg, char *line, int *i, t_fix *fix);
int     ft_realloc_fix_error(char **arg, t_fix *fix);
char    *ft_strjoin_free(char *s, char const *s2);
int    ft_new_input(t_command *c, char *line, int *i, t_fix *fix);
int    ft_new_out(t_command *c, char *line, int *i, t_fix *fix);
int    ft_ambiguous_redir(char *line, int i_start, int *i, t_fix *fix);
int    ft_empty_redir(t_fix *fix);
void    ft_close_quotes(char *line, int *i, int *quote);
int    ft_syntax_error(t_fix *fix, char *s);
int		ft_global_parse(char *line, char *c);
int	ft_cmd_parse(char *sub, char *c);

t_fix	fix;

#endif
