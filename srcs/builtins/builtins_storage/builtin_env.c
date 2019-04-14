/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_env.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 22:37:30 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 02:59:08 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_storage/builtin_env.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <sys/types.h>

void	handle(int signo)
{
	dprintf(2, "env received %d\n", signo);
}

int		builtin_env(t_sh_state *sh_state, int ac, const char **av,
t_builtin_context *context)
{
	sleep(5);
	print_env(sh_state->internal_storage, context->fds.out);
	sleep(5);
	dprintf(2, "-------------------------------------------\n");
	return (1);
}
