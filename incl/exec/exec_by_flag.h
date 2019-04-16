/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_by_flag.h                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 02:56:33 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 03:03:18 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXEC_BY_FLAG_H
# define EXEC_BY_FLAG_H

# include "common.h"
# include "builtins/builtins.h"
# include "exec/exec_dispatcher.h"

int			exec_no_flag(t_sh_state *sh_state, t_cmd *cmd, t_context *context);
int			exec_pipe_flag(t_sh_state *sh_state, t_cmd *cmd,
			t_context *context);
int			exec_conditioned_flag(t_sh_state *sh_state, t_cmd *cmd,
			t_context *context);

#endif
