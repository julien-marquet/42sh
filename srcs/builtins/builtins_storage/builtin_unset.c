/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_unset.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 23:23:29 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 05:57:41 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_storage/builtin_unset.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

int		builtin_unset(t_sh_state *sh_state, int ac, const char **av,
t_builtin_context *context)
{
	int		i;

	i = 1;
	while (i < ac)
		remove_entry_storage(sh_state, &sh_state->internal_storage, av[i++]);
	i = 1;
	return (0);
}
