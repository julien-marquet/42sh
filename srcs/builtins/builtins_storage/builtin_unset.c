/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_unset.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 23:23:29 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 02:01:13 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_storage/builtin_unset.h"

int		builtin_unset(t_sh_state *sh_state, int ac, const char **av,
const t_fds fds)
{
	int		i;

	i = 1;
	while (i < ac)
		remove_entry_storage(&sh_state->internal_storage, av[i++]);
	i = fds.out;
	return (0);
}
