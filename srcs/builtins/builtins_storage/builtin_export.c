/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_export.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 23:37:38 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 18:01:17 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_storage/builtin_export.h"

int		builtin_export(t_sh_state *sh_state, int ac, const char **av,
t_builtin_context *context)
{
	int		i;

	if (ac == 1)
		print_env(sh_state->internal_storage, context->fds.out);
	else
	{
		i = 1;
		while (i < ac)
			update_exported_flag(sh_state->internal_storage, av[i++], 1);
	}
	return (0);
}
