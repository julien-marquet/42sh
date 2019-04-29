/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error_handler.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 18:10:51 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 15:18:45 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "error_handler.h"

int		print_error(const char *origin, const char *err, int fd)
{
	int		olen;
	int		elen;

	if (!origin || !err)
		return (-1);
	if (write(fd, origin, (olen = ft_strlen(origin))) == -1)
		return (-1);
	if (write(fd, err, (elen = ft_strlen(err))) == -1)
		return (-1);
	return (olen + elen);
}

void	handle_path_exec_error(const char *origin, const char *path, int err)
{
	char	*str;

	if (path == NULL)
		return ;
	else if (err == 0)
		str = ft_construct_str(2, path, ": no such file or directory");
	else if (err == 1)
		str = ft_construct_str(2, path, ": permission denied");
	else if (err == 2)
		str = ft_construct_str(2, path, ": is not a regular file");
	print_error(origin, str, 2);
	ft_strdel(&str);
}

void	handle_path_error(const char *origin, const char *path, int err)
{
	char	*str;

	if (err == 0)
		str = ft_construct_str(2, path, ": command not found");
	else if (err == 1)
		str = ft_construct_str(2, path, ": permission denied");
	else if (err == 2)
		str = ft_construct_str(2, path, ": is not a regular file");
	print_error(origin, str, 2);
	ft_strdel(&str);
}

void	handle_no_dir_error(const char *origin, const char *path, int err)
{
	char	*str;

	if (err == 1)
		str = ft_construct_str(2, path, ": no such file or directory");
	else if (err == 2)
		str = ft_construct_str(2, path, ": permission denied");
	else if (err == 3)
		str = ft_construct_str(2, path, ": is a directory");
	print_error(origin, str, 2);
	ft_strdel(&str);
}

void	handle_dir_path_error(const char *origin, const char *path, int err)
{
	char	*str;

	if (err == 1)
		str = ft_construct_str(2, path, ": no such file or directory");
	else if (err == 2)
		str = ft_construct_str(2, path, ": permission denied");
	else if (err == 3)
		str = ft_construct_str(2, path, ": Not a directory");
	print_error(origin, str, 2);
	ft_strdel(&str);
}