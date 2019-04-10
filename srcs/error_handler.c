/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error_handler.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 18:10:51 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 18:31:41 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "error_handler.h"

void	print_error(const char *origin, const char *err, int fd)
{
	ft_putstr_fd(origin, fd);
	ft_putendl_fd(err, fd);
}
