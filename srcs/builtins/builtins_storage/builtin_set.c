/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_set.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:47:16 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 01:59:11 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_storage/builtin_set.h"

int		builtin_set(t_sh_state *sh_state, int ac, const char **av, const t_fds fds)
{
	ac = !!av;
	print_storage_content(sh_state->internal_storage, fds.out);
	return (0);
}
