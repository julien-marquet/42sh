/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_unsetenv.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 21:00:21 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 18:28:27 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_storage/builtin_unsetenv.h"

int		builtin_unsetenv(t_sh_state *sh_state, int ac,
const char **av, t_builtin_context *context)
{
	int		i;

	if (ac == 1)
	{
		write(context->fds.err, "unsetenv: Too few arguments.\n", 30);
		return (1);
	}
	else
	{
		i = 1;
		while (i < ac)
			update_exported_flag(sh_state->internal_storage, av[i++], 0);
		return (0);
	}
}
