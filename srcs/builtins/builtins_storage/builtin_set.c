/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_set.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:47:16 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 23:22:16 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_storage/builtin_set.h"

int		builtin_set(t_sh_state *sh_state, int ac, const char **av, int fd_out)
{
	ac = !!av;
	print_storage_content(sh_state->internal_storage, fd_out);
	return (0);
}
