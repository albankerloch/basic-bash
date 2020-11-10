/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:47:27 by aduchemi          #+#    #+#             */
/*   Updated: 2020/11/10 15:53:51 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <signal.h>
# include <errno.h>
# include <string.h>

typedef	struct	s_command
{
	char	**arg;
	int		input;
	char	*n_input;
	int		add;
	int		quote;
	char	*n_out;
	int		k;
}				t_command;

typedef	struct	s_f
{
	int		error;
	int		exit;
	char	**env;
	char	*line;
}				t_f;

int				ft_parser_exec(char *line, t_f *g_f);
int				ft_parse_line(char *line, t_f *g_f, int *i);
int				ft_parser(t_list *t, char *line, int *i);
int				ft_parser_arg(t_list **t, char *line, int *i, t_command	**c);
int				ft_parser_symbol(t_list *t, char *line, int *i, t_command	*c);
int				ft_exec(t_list *t, char *line, t_f *g_f);
void			ft_child_exec(t_list *t, t_f *g_f, int pipe_fd[2]);
int				ft_parent_exec(t_list *t, char *line, t_f *g_f, int pipe_fd[2]);
char			*ft_env_var(char *arg, int h, t_f *g_f);
int				ft_arg_var(char **arg, t_f *g_f);
void			ft_f_construct(t_f *g_f, char **envp, int argc, char *argv[]);
char			*ft_realloc_concat(char *line, char c);
int				ft_redirections(t_list *t, char *line, int *i);
int				ft_redirection_right(t_command *c, char *line, int *i);
int				ft_redirection_left(t_command *c, char *line, int *i);
int				ft_redir_right(t_command *c, char *line, int *i);
int				ft_backslash(char *line, int *i, int *quote);
char			**ft_realloc_arg(char **arg);
void			ft_skip_quotes(char *line, int *i, int *quote);
t_command		*ft_command_construct();
void			ft_command_destroy(void *c);
int				ft_touch(t_command *c);
int				ft_checkfile(t_command *c, char *line, int *i);
int				ft_open_redir(t_command *c);
int				ft_builtins(t_command *c, int fd);
int				ft_fork_exec_cmd(t_command *c, t_f *g_f);
int				ft_loop_absolute_path(t_command *c, int j, int k,\
char try_path[PATH_MAX]);
int				ft_absolute_path(t_command *c);
int				ft_new_arg(t_command *c, char *line, int *i, int *k);
int				ft_new_arg_var(char **arg, char *line, int *i, int *quote);
int				ft_redir_var(int quote, char *line, int *i, char **arg);
int				ft_arg(t_command *c, char *line, int *i, int *k);
void			ft_env_destroy(char **env);
void			ft_sig_handler(int signum);
void			ft_sig_handler_process(int signum);
void			ft_sig_handler_quit(int signum);
int				ft_syntax_export(t_command *c, int fd, t_f *g_f);
int				ft_export_without_arg(t_f *g_f, int fd);
int				ft_export_err(char *arg);
int				ft_env_err(t_command *c);
void			ft_execve(t_command *c, t_f *g_f);
int				ft_redir_execve(t_command *c, int fd);
void			ft_fork_execve(t_command *c, t_f *g_f);
char			**ft_realloc_env(t_f *g_f, char buf[PATH_MAX]);
void			ft_strjoin_buff(char s1[PATH_MAX], char s2[PATH_MAX]);
void			ft_realloc_concat_buff(char line[PATH_MAX], char c);
void			ft_error(int err);
void			ft_error_errno(char *cmd, char *arg, int err);
void			ft_custom_error(char *cmd, char *arg, char *message);
void			ft_cmd_error(char *str, char *message);
void			ft_cmd_error_errno(char *str, char *cmd, char *arg, int err);
int				ft_echo(t_command *c, int fd);
int				ft_env(t_command *c, int fd);
int				ft_pwd(int fd);
int				ft_export(t_command *c, int fd);
int				ft_unset(t_command *c);
int				ft_cd(t_command *c);
int				ft_builtin_exit(t_command *c);
int				ft_env_len(t_f *g_f);
char			**ft_replace_env(char *arg, int egal);
char			*ft_join_end_var(char *val_var, char *arg, int j);
char			*ft_valeur_variable(t_f *g_f, char *nom_var);
void			ft_echo_n(int *n, char **arg, int *i);
int				ft_exit_f(t_f *g_f, int i, int e);
void			ft_exit(t_f *g_f, char *line, int e);
t_command		*ft_free_part_command(t_command *c, int i);
void			ft_del_command(void *c);
void			ft_free_command(t_command *c);
t_list			*ft_init_list(void);
int				ft_add_list(t_list *t);
char			**ft_free_tab(char **new, int i);
char			*ft_substr_strjoin(char const *s,\
unsigned int start, size_t len, char const *s2);
char			*ft_strjoin_substr(char const *s1,\
char const *s, unsigned int start, size_t len);
int				ft_isnum(char *str);
int				ft_export_egal(t_command *c, int i);
void			ft_aff_export_without_arg(int i, int *j, int fd);
int				ft_env_compare(char *arg, int n);
int				ft_export_check_id(char *arg, int i);
char			**ft_unset_env(t_f *g_f, char *arg);
int				ft_realloc_var(char **arg, char *line, int *i);
int				ft_realloc_g_f_error(char **arg, int *i);
char			*ft_strjoin_free(char *s, char const *s2);
int				ft_new_in_out(t_command *c, char **arg, char *line, int *i);
int				ft_quotes(char *line, int *i, int *quote, int *ret);
int				ft_ambiguous_redir(char *line, int i_start, int *i);
int				ft_empty_redir(t_f *g_f);
void			ft_close_quotes(char *line, int *i, int *quote);
int				ft_syntax_error(char *s);
int				ft_global_parse(char *line, char *c);
int				ft_cmd_parse(char *sub, char *c);
int				ft_sub_parse(char *line, int i, int needle, char *c);
int				ft_check_atoi(const char *str);
int				ft_len_sub_parse(char *line, int *quote, int *needle);

t_f				g_f;
#endif
