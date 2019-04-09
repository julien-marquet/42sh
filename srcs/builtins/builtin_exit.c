/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_exit.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 22:38:07 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 02:01:45 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_exit.h"

int		builtin_exit(t_sh_state *sh_state, int ac, const char **av, const t_fds fds)
{
	if (ac > 2)
	{
		write(fds.err, "exit:, Too many arguments.\n", 29);
		return (1);
	}
	sh_state->exit_sig = 1;
	if (ac > 1)
		return (ft_atoi(av[1]));
	else
		return ((int)sh_state->status);
}
