/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_jobs.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/11 20:45:56 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 23:32:25 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_jobs/builtin_jobs.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

int			builtin_jobs(t_sh_state *sh_state, int ac,
const char **av, t_builtin_context *context)
{
	list_jobs();
	return (0);
}