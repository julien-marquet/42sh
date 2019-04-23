/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error_handler.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 18:10:51 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 04:00:43 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "error_handler.h"

void	print_error(const char *origin, const char *err, int fd)
{
	ft_putstr_fd(origin, fd);
	ft_putendl_fd(err, fd);
}

void	handle_path_error(const char *origin, const char *path, int err)
{
	char	*str;

	if (err == 1)
		str = ft_construct_str(2, path, ": no such file or directory\n");
	else if (err == 2)
		str = ft_construct_str(2, path, ": permission denied\n");
	else if (err == 3)
		str = ft_construct_str(2, path, ": is not a regular file\n");
	print_error(origin, str, 2);
	ft_strdel(&str);
}

void	handle_dir_path_error(const char *origin, const char *path, int err)
{
	char	*str;

	if (err == 1)
		str = ft_construct_str(2, path, ": no such file or directory\n");
	else if (err == 2)
		str = ft_construct_str(2, path, ": permission denied\n");
	else if (err == 3)
		str = ft_construct_str(2, path, ": Not a directory\n");
	print_error(origin, str, 2);
	ft_strdel(&str);
}