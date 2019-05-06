/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_unsetenv.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 21:00:21 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 19:22:13 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_storage/builtin_unsetenv.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

int		unset_var(t_sh_state *sh_state, t_list **table, const char *arg)
{
	if (get_env_value(sh_state->internal_storage, arg) == NULL)
		return (0);
	remove_entry_storage(sh_state, &sh_state->internal_storage, arg);
	return (0);
}

int		builtin_unsetenv(t_sh_state *sh_state, int ac,
const char **av, t_builtin_context *context)
{
	int		i;

	if (ac == 1)
	{
		write(2, "unsetenv: Too few arguments.\n", 30);
		return (1);
	}
	else
	{
		i = 1;
		while (i < ac)
		{
			unset_var(sh_state,
		&(sh_state->hash_table), av[i++]);
		}
		return (0);
	}
}
