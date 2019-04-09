/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_echo.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 22:59:24 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 02:01:38 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_echo.h"

int			builtin_echo(t_sh_state *sh_state, int ac,
const char **av, const t_fds fds)
{
	int		i;

	sh_state->status = sh_state->status;
	i = 1;
	while (i < ac)
	{
		ft_putstr_fd(av[i], fds.out);
		write(fds.out, " ", 1);
		i++;
	}
	write(fds.out, "\n", 1);
	return (0);
}
