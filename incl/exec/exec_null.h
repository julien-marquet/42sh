/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_null.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 19:51:26 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 19:55:30 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXEC_NULL_H
# define EXEC_NULL_H

# include "common.h"
# include "exec/exec_dispatcher.h"
# include "exec/exec_cmd_checkers.h"
# include "jobs/jobs.h"

int		handle_null_cmd(t_sh_state *sh_state, t_cmd **cmd,
		t_context *context, int err);

#endif
