/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_set.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:47:16 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 18:28:11 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_storage/builtin_set.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

int		builtin_set(t_sh_state *sh_state, int ac, const char **av, t_builtin_context *context)
{
	print_storage_content(sh_state->internal_storage, context->fds.out);
	return (0);
}
