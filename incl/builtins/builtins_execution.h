/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_execution.h                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 19:16:54 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 23:01:26 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTINS_EXECUTION_H
# define BUILTINS_EXECUTION_H

# include "common.h"
# include "term_state.h"
# include "builtins/builtins_defines.h"
# include "jobs/jobs.h"

int		exec_builtin(t_sh_state *sh_state, const char **av,
		t_builtin_func builtin, t_context *context);
int		exec_builtin_solo(t_sh_state *sh_state, const char **av,
		t_builtin_func builtin, t_context *context);

#endif
