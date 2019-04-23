/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirs.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/22 23:15:36 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 03:16:50 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "pipe_redir/redirs.h"

int		handle_here(t_file *in)
{
	int		new_pipe[3];

	if (pipe(&new_pipe[1]) != 0)
		return (1);
	new_pipe[0] = 1;
	ft_putstr_fd(in->here, new_pipe[WRITE_END]);
	dup2(new_pipe[READ_END], 0);
	close(new_pipe[READ_END]);
	close(new_pipe[WRITE_END]);
	return (0);
}

int		check_file_read(const char *path)
{
	struct stat	f_stat;

	if (path == NULL)
		return (-1);
	if (access(path, F_OK) == -1)
		return (1);
	if (access(path, R_OK) == -1)
		return (2);
	if (stat(path, &f_stat) == -1)
		return (-1);
	if (S_ISREG(f_stat.st_mode) == 0)
		return (3);
	return (0);
}

int		modify_path(char **path)
{
	char	*cpy;
	if (path == NULL || *path == NULL)
		return (1);
	if (ft_strchr((const char *)*path, '/') == NULL)
	{
		cpy = *path;
		if ((*path = ft_memalloc(ft_strlen((const char *)*path) + 3)) == NULL)
			return (1);
		ft_strcpy(*path, "./");
		ft_strcpy(*path, cpy);
		ft_strdel(&cpy);
	}
	return (0);
}

int		handle_file_in(t_file *in)
{
	int		err;
	int		fd;

	if ((modify_path(&in->file)) == 1)
		return (-1);
	if ((err = check_file_read(in->file)) != 0)
		return (err);
	else
	{
		fd = open(in->file, O_RDONLY);
		dup2(fd, 0);
		close(fd);
	}
	return (0);
}

void	handle_fd_error(t_file *in, char *origin)
{
	char	*err;

	err = ft_construct_str(2, in->file, ": Bad file descriptor");
	print_error(origin, err, 2);
	ft_strdel(&err);
}

int		handle_signal_in(t_file *in)
{
	if (in->type[C_IN] != -1 && in->type[C_OUT] != -1)
	{
		if (dup2(in->type[C_OUT], in->type[C_IN]) == -1)
			return (1);
	}
	return (0);
}

int		handle_in(t_file *in, char *origin)
{
	int		err;

	while (in != NULL)
	{
		if (in->here != NULL)
		{
			if ((err = handle_here(in)) != 0)
				return (-1);
		}
		else if (in->type[C_OUT] != -1)
		{
			if ((err = handle_signal_in(in)) != 0)
			{
				handle_fd_error(in, origin);
				return (1);
			}
		}
		else if (in->file != NULL)
		{
			if ((err = handle_file_in(in)) != 0)
			{
				handle_path_error(origin, in->file, err);
				return (err);
			}
		}
		else
			return (-1);
		in = in->next;
	}
	return (0);
}

int		handle_out(t_file *out, char *origin)
{
	while (out != NULL)
	{
		dprintf(2, "OUT NODE\n");
		dprintf(2, "orig = %s\n", origin);
		out = out->next;
	}
	return (0);
}

int		handle_redir(t_cmd *cmd, char *origin)
{
	int		err;

	if (cmd->in != NULL)
	{
		if ((err = handle_in(cmd->in, origin)) != 0)
			return (err);
	}
	if (cmd->out != NULL)
	{
		if ((err = handle_out(cmd->out, origin)) != 0)
			return (err);
	}
	return (0);
}

/*
**	OUT -1  no redir in canal -2 close
**	IN 1 default 0 chev gauche default * value of in
*/