/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_set.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:47:16 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 19:36:33 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_storage/builtins_set.h"

// @TODO PRINT VARS

int		builtins_set(t_sh_state *sh_state, int fd_out)
{
	print_storage_content(sh_state->env, fd_out);
	return (0);
}
