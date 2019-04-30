/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_false.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/30 10:00:22 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 10:03:27 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_false.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

int		builtin_false(t_sh_state *sh_state, int ac,
const char **av, t_builtin_context *context)
{
	return (1);
}
