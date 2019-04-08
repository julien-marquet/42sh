/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_unalias.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 00:13:30 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 01:44:27 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_aliases/builtin_unalias.h"

int		builtin_unalias(t_sh_state *sh_state, int ac, const char **av,
int fd_out)
{
	int		res;
	int		i;

	res = 0;
	if (ac <= 1)
	{
		write(fd_out, "unalias: usage: unalias name [name ...]\n", 41);
		res = 1;
	}
	else
	{
		i = 1;
		while (i < ac)
		{
			if (remove_alias(&sh_state->aliases, av[i]) == 0)
			{
				write(2, "unalias: ", 9);
				ft_putstr_fd(av[i], 2);
				write(2, ": not found\n", 12);
				res = 1;
			}
			i++;
		}
	}
	return (res);
}
