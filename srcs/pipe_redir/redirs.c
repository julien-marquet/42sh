/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirs.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/22 23:15:36 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 19:49:07 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "pipe_redir/redirs.h"

int		dir_write_error(char *origin, t_file *out, char **dir_path, int err)
{
	handle_dir_path_error((const char *)origin, (const char *)out->file, err);
	ft_strdel(dir_path);
	return (err);
}

int		handle_file_out(t_file *out, char *origin)
{
	int		err;
	char	*dir_path;
	int		fd;
	int		open_flags;

	if ((err = check_file_write(out->file)) != 0)
	{
		if (err == 1)
		{
			if ((dir_path = get_parent_dir_path(out->file)) == NULL)
				return (-1);
			if ((err = check_dir_write(dir_path)) != 0)
				return (dir_write_error(origin, out, &dir_path, err));
			ft_strdel(&dir_path);
		}
		else
			return (redirs_exit2(origin, out, err));
	}
	open_flags = O_WRONLY;
	open_flags |= out->type[C_LEN] == 2 ? O_APPEND : O_TRUNC;
	if ((fd = open(out->file, open_flags)) == -1)
		return (-1);
	if (out->type[C_IN] <= 2)
		dup2(fd, out->type[C_IN]);
	return (close(fd));
}

int		handle_out(t_file *out, char *origin)
{
	int		err;

	while (out != NULL)
	{
		if (out->type[C_OUT] != -1)
		{
			if ((err = handle_signal(out)) != 0)
			{
				handle_fd_error(out, origin);
				return (1);
			}
		}
		else if (out->file != NULL)
		{
			if ((err = handle_file_out(out, origin)) != 0)
				return (err);
		}
		else
			return (-1);
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
