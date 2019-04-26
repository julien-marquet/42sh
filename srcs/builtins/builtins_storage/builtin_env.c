/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_env.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 22:37:30 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 05:35:32 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_storage/builtin_env.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

int		builtin_env(t_sh_state *sh_state, int ac, const char **av,
t_builtin_context *context)
{
	print_env(sh_state->internal_storage, context->fds.out);
	return (0);
}
