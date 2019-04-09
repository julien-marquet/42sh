/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_unalias.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 00:13:30 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 01:53:43 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_aliases/builtin_unalias.h"

int		builtin_unalias(t_sh_state *sh_state, int ac, const char **av,
const t_fds fds)
{
	int		res;
	int		i;

	res = 0;
	if (ac <= 1)
	{
		write(fds.err, "unalias: usage: unalias name [name ...]\n", 41);
		res = 1;
	}
	else
	{
		i = 1;
		while (i < ac)
		{
			if (remove_alias(&sh_state->aliases, av[i]) == 0)
			{
				write(fds.err, "unalias: ", 9);
				ft_putstr_fd(av[i], fds.err);
				write(fds.err, ": not found\n", 12);
				res = 1;
			}
			i++;
		}
	}
	return (res);
}
