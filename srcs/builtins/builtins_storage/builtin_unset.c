/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_unset.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 23:23:29 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 01:20:26 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_storage/builtin_unset.h"

int		builtin_unset(t_sh_state *sh_state, int ac, const char **av, int fd_out)
{
	int		i;

	fd_out++;
	i = 1;
	while (i < ac)
	{
		remove_entry_storage(&sh_state->internal_storage, av[i]);
		i++;
	}
	return (0);
}
