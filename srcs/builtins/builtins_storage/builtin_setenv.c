/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_setenv.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 19:39:26 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 00:06:46 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_storage/builtin_setenv.h"

int			builtin_setenv(t_sh_state *sh_state, int ac,
const char **av, t_builtin_context *context)
{
	int		res;

	add_origin(&context->origin, "setenv");
	res = 0;
	if (ac == 1)
		res = builtin_env(sh_state, ac, av, context);
	else if (ac > 3)
		write(context->fds.err, "setenv:, Too many arguments.\n", 30);
	else
	{
		if ((res = add_entry_storage(sh_state, av[1], av[2], 1)) == -1)
			return (1);
		else if (res == 1)
		{
			print_error(context->origin,
		"Variable name must only contains alphanumerical characters or \'_\'",
		context->fds.err);
		}
	}
	return (res);
}
