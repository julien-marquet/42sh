/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirs2.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 05:41:44 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 05:41:45 by legrivel    ###    #+. /#+    ###.fr     */
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
