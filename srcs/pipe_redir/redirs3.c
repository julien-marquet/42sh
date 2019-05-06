/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirs3.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 05:41:54 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 05:41:55 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "pipe_redir/redirs.h"

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

int		redirs_exit(t_file *in, char *origin)
{
	handle_fd_error(in, origin);
	return (1);
}

int		redirs_exit2(char *origin, t_file *in, int err)
{
	handle_no_dir_error(origin, in->file, err);
	return (err);
}
