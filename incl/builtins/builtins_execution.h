/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_execution.h                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 19:16:54 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 20:55:33 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTINS_EXECUTION_H
# define BUILTINS_EXECUTION_H

# include "common.h"
# include "term_state.h"
# include "builtins/builtins_defines.h"

int		exec_builtin(t_sh_state *sh_state, const char **av,
		t_builtin_func builtin, int fd_out);
int		background_exec_builtin(t_sh_state *sh_state, const char **av,
t_builtin_func builtin, int fd_out);

#endif
