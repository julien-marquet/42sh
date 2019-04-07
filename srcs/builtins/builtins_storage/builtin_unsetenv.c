/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_unsetenv.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 21:00:21 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 21:15:07 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_storage/builtin_unsetenv.h"

int		builtin_unsetenv(t_sh_state *sh_state, int ac,
const char **av, int fd_out)
{
	int		i;

	if (ac == 1)
	{
		write(fd_out, "unsetenv: Too few arguments.\n", 30);
		return (1);
	}
	else
	{
		i = 1;
		while (i < ac)
		{
			remove_entry_storage(&sh_state->env, av[i]);
			i++;
		}
		return (0);
	}
}
