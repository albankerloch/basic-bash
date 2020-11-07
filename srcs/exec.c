/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:24:18 by aduchemi          #+#    #+#             */
/*   Updated: 2020/07/15 16:59:40 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_parent_exec(t_list *t, char *line, t_f *g_f, int pipe_fd[2])
{
	int save_fd;

	t = t->next;
	if ((save_fd = dup(0)) == -1)
		return (0);
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], 0) == -1)
		return (0);
	close(pipe_fd[0]);
	if (ft_exec(t, line, g_f) == 0)
		return (0);
	if (dup2(save_fd, 0) == -1)
		return (0);
	close(save_fd);
	return (1);
}

void	ft_child_exec(t_list *t, char *line, t_f *g_f, int pipe_fd[2])
{
	int	save_fd;
	int	ret;

	if ((save_fd = dup(1)) == -1)
		exit(-1);
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], 1) == -1)
		exit(-1);
	close(pipe_fd[1]);
	if ((ret = ft_fork_exec_cmd(t->content, line, g_f)) == 0 || ret == -1)
		exit(-1);
	if (dup2(save_fd, 1) == -1)
		exit(-1);
	close(save_fd);
	exit(0);
}

int		ft_exec(t_list *t, char *line, t_f *g_f)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		error;

	error = 1;
	if (!t->next)
		return (ft_fork_exec_cmd(t->content, line, g_f));
	else
	{
		pipe(pipe_fd);
		pid = fork();
		if (pid == 0)
			ft_child_exec(t, line, g_f, pipe_fd);
		else
		{
			if (!(ft_parent_exec(t, line, g_f, pipe_fd)))
				return (0);
			wait(&error);
		}
	}
	if (error != 0)
		return (-1);
	return (1);
}

void	ft_fork_execve(t_command *c, t_f *g_f)
{
	pid_t	pidf;
	int		status;

	pidf = fork();
	if (pidf == 0)
	{
		signal(SIGINT, ft_sig_handler_process);
		signal(SIGQUIT, SIG_DFL);
		ft_execve(c, g_f);
	}
	else
	{
		signal(SIGINT, ft_sig_handler_process);
		signal(SIGQUIT, ft_sig_handler_process);
		wait(&status);
	}
	if (WIFEXITED(status))
		g_f->error = WEXITSTATUS(status);
}

int		ft_fork_exec_cmd(t_command *c, char *line, t_f *g_f)
{
	char	***p;
	int		ret;
	int		fd;

	if ((fd = ft_open_redir(c)) == -1)
		return (0);
	if ((ret = ft_builtins(c, line, g_f, fd)) == 0)
	{
		if (c->add != 0)
			close(fd);
		return (0);
	}
	else if (ret == 1)
		g_f->error = 0;
	else if (ret == -1)
		ft_fork_execve(c, g_f);
	if (c->add != 0)
		close(fd);
	return (1);
}
