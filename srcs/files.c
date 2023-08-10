/**
* @file files.c
* @author alban kerloc'h
* @date 11/10/2019
* @version 1.0
*/

#include "../includes/minishell.h"

int		ft_touch(t_command *c)
{
	int		fd;

	if (c->add == 1)
		fd = open(c->n_out, O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR |
		S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	else if (c->add == 2)
		fd = open(c->n_out, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR |
		S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	else
		fd = 0;
	if (fd == -1)
	{
		ft_error_errno("bash", c->n_out, errno);
		return (-1);
	}
	if (c->add != 0)
		close(fd);
	return (1);
}

int		ft_open_redir(t_command *c)
{
	int		fd;

	if (c->add == 0)
		fd = 1;
	else if (c->add == 1)
		fd = open(c->n_out, O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR |
		S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	else
		fd = open(c->n_out, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR |
		S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd == -1)
	{
		ft_error_errno("bash", c->n_out, errno);
		return (-1);
	}
	return (fd);
}

int		ft_checkfile(t_command *c, char *line, int *i)
{
	struct stat	buffer;

	if (stat(c->n_input, &buffer) != 0)
	{
		ft_error_errno(c->arg[0], c->n_input, errno);
		while (line[*i] && line[*i] != ';')
			(*i)++;
		if (line[*i] == ';')
			(*i)++;
		g_f.error = 1;
		return (-1);
	}
	return (1);
}
