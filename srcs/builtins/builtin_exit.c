/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_exit.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 22:38:07 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 22:56:16 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_exit.h"

int		builtin_exit(t_sh_state *sh_state, int ac, const char **av, int fd_out)
{
	if (ac > 2)
	{
		write(fd_out, "exit:, Too many arguments.\n", 29);
		return (1);
	}
	sh_state->exit_sig = 1;
	if (ac > 1)
		return (ft_atoi(av[1]));
	else
		return (sh_state->status);
}
