/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_by_flag.h                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 02:56:33 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 22:33:26 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXEC_BY_FLAG_H
# define EXEC_BY_FLAG_H

# include "common.h"
# include "builtins/builtins.h"
# include "exec/exec_dispatcher.h"
# include "exec/exec_cmd_checkers.h"
# include "jobs/jobs_procs/jobs_procs.h"

int			exec_end_flag(t_sh_state *sh_state, t_cmd *cmd, t_context *context);
int			exec_pipe_flag(t_sh_state *sh_state, t_cmd *cmd,
			t_context *context);
int			exec_conditioned_flag(t_sh_state *sh_state, t_cmd *cmd,
			t_context *context);

#endif
