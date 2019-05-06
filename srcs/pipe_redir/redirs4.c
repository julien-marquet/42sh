/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirs4.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 05:42:48 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 05:42:49 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "pipe_redir/redirs.h"

int			handle_in(t_file *in, char *origin)
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
				return (redirs_exit(in, origin));
		}
		else if (in->file != NULL)
		{
			if ((err = handle_file_in(in)) != 0)
				return (redirs_exit2(origin, in, err));
		}
		else
			return (-1);
		in = in->next;
	}
	return (0);
}

static void	handle_error(int *err, char **origin, t_file *out)
{
	*err = *err == -1 ? *err : *err - 1;
	add_origin(origin, NAME);
	handle_path_exec_error(*origin, out->file, *err);
	ft_strdel(origin);
}

static void	pre_handle_exec(char **origin, t_file *out, int err)
{
	add_origin(origin, NAME);
	handle_path_exec_error(*origin, out->file, err);
	ft_strdel(origin);
}

int			loop_cmd(t_cmd *acmd, t_file *out, char **origin)
{
	int		fd;
	int		err;
	char	*dir_path;

	if (acmd->out->type[C_OUT] == -1 && acmd->out->file != NULL)
	{
		err = 0;
		if ((err = check_file_write(out->file)) != 0)
		{
			if (err == 1)
			{
				if ((dir_path = get_parent_dir_path(out->file)) == NULL)
					return (-1);
				if ((err = check_dir_write(dir_path)) != 0)
					handle_error(&err, origin, out);
				ft_strdel(&dir_path);
			}
			else
				pre_handle_exec(origin, out, err);
		}
		if (err == 0)
			if ((fd = open(out->file, O_CREAT | O_NONBLOCK, 0666)) != -1)
				close(fd);
	}
	return (0);
}

int			create_redir_files(t_cmd *acmd)
{
	t_file	*out;
	char	*origin;

	origin = NULL;
	while (acmd != NULL)
	{
		out = acmd->out;
		while (out != NULL)
		{
			if (loop_cmd(acmd, out, &origin) == -1)
				return (-1);
			out = out->next;
		}
		if (acmd->red != NULL && (ft_strcmp(acmd->red, "&&") == 0 ||
		ft_strcmp(acmd->red, "||") == 0))
			break ;
		acmd = acmd->next;
	}
	return (0);
}
