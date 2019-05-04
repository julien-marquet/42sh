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
	if (S_ISDIR(f_stat.st_mode) == 1)
		return (3);
	return (0);
}

int		check_file_write(const char *path)
{
	struct stat	f_stat;

	if (path == NULL)
		return (-1);
	if (access(path, F_OK) == -1)
		return (1);
	if (access(path, W_OK) == -1)
		return (2);
	if (stat(path, &f_stat) == -1)
		return (-1);
	if (S_ISDIR(f_stat.st_mode) == 1)
		return (3);
	return (0);
}


int		check_dir_write(const char *path)
{
	struct stat	f_stat;

	if (path == NULL)
		return (-1);
	if (access(path, F_OK) == -1)
		return (1);
	if (access(path, W_OK) == -1)
		return (2);
	if (stat(path, &f_stat) == -1)
		return (-1);
	if (S_ISDIR(f_stat.st_mode) == 0)
		return (3);
	return (0);
}

char	*get_parent_dir_path(const char *path)
{
	char	*last_slash;
	size_t	i;

	if ((last_slash = strrchr(path, '/')) == NULL)
		return (ft_strdup("."));
	else
	{
		i = 0;
		while (&(path[i]) != last_slash)
			i++;
		return (ft_strndup(path, i));
	}
}

int		handle_file_in(t_file *in)
{
	int		err;
	int		fd;

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

int		handle_signal(t_file *file)
{
	if (file->type[C_OUT] >= 0)
	{
		if (file->type[C_OUT] > 2)
			return (1);
		if (dup2(file->type[C_OUT], file->type[C_IN]) == -1)
			return (1);
	}
	else
		close(file->type[C_IN]);
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
			if ((err = handle_signal(in)) != 0)
			{
				handle_fd_error(in, origin);
				return (1);
			}
		}
		else if (in->file != NULL)
		{
			if ((err = handle_file_in(in)) != 0)
			{
				handle_no_dir_error(origin, in->file, err);
				return (err);
			}
		}
		else
			return (-1);
		in = in->next;
	}
	return (0);
}

int		create_redir_files(t_cmd *acmd)
{
	int		err;
	char	*dir_path;
	int		fd;
	t_file	*out;
	char	*origin;

	origin = NULL;
	while (acmd != NULL)
	{
		out = acmd->out;
		while (out != NULL)
		{
			if (acmd->out->type[C_OUT] == -1 &&
		acmd->out->file != NULL)
			{
				err = 0;
				if ((err = check_file_write(out->file)) != 0)
				{
					if (err == 1)
					{
						if ((dir_path = get_parent_dir_path(out->file)) == NULL)
							return (-1);
						if ((err = check_dir_write(dir_path)) != 0)
						{
							err = err == -1 ? err : err - 1;
							add_origin(&origin, NAME);
							handle_path_exec_error(origin, out->file, err);
							ft_strdel(&origin);
						}
						ft_strdel(&dir_path);
					}
					else
					{
						add_origin(&origin, NAME);
						handle_path_exec_error(origin, out->file, err);
						ft_strdel(&origin);
					}
				}
				if (err == 0)
				{
					if ((fd = open(out->file, O_CREAT|O_NONBLOCK, 0666)) != -1)
						close(fd);
				}
			}
			out = out->next;
		}
		if (acmd->red != NULL && (ft_strcmp(acmd->red, "&&") == 0 ||
		ft_strcmp(acmd->red, "||") == 0))
			break ;
		acmd = acmd->next;
	}
	return (0);
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
			{
				handle_dir_path_error((const char *)origin,
			(const char *)out->file, err);
				ft_strdel(&dir_path);
				return (err);
			}
			ft_strdel(&dir_path);
		}
		else
		{
			handle_no_dir_error(origin, out->file, err);
			return (err);
		}
	}
	open_flags = O_WRONLY;
	open_flags |= out->type[C_LEN] == 2 ? O_APPEND : O_TRUNC;
	if ((fd = open(out->file, open_flags)) == -1)
		return (-1);
	if (out->type[C_IN] <= 2)
		dup2(fd, out->type[C_IN]);
	close(fd);
	return (0);
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
