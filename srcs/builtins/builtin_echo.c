/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_echo.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 22:59:24 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 23:05:49 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_echo.h"

int			builtin_echo(t_sh_state *sh_state, int ac,
const char **av, int fd_out)
{
	int		i;

	sh_state->status = sh_state->status;
	i = 1;
	while (i < ac)
	{
		ft_putstr_fd(av[i], fd_out);
		write(fd_out, " ", 1);
		i++;
	}
	write(fd_out, "\n", 1);
	return (0);
}
