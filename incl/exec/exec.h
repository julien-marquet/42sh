/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 23:13:44 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/20 23:21:25 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "common.h"
# include "exec/exec_by_flag.h"
# include "exec/exec_utils.h"
# include "exec/exec_dispatcher.h"
# include "exec/exec_binary.h"
# include "parse/parse.h"

int		exec_cmd_list(t_sh_state *sh_state, t_cmd *cmd_list,
		const char *job_name, t_proc_grp *prec_grp);

#endif
