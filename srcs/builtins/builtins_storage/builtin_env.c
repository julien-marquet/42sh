/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_env.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 22:37:30 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/20 03:19:37 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_storage/builtin_env.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "signal.h"
#include <sys/types.h>

int		builtin_env(t_sh_state *sh_state, int ac, const char **av,
t_builtin_context *context)
{
	int		i;
	i = 0;
	while (i < INT32_MAX)
	{
		i++;
	}
	print_env(sh_state->internal_storage, context->fds.out);
	dprintf(2, "-------------------------------------------\n");
	return (0);
}
