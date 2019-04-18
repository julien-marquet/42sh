/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_procs_setters.h                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:55:02 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 23:54:50 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef JOBS_PROCS_SETTERS_H
# define JOBS_PROCS_SETTERS_H

# include "common.h"
# include "exec/exec_cmd_checkers.h"

t_proc		*new_proc(int pid, const char *name, int last);
int			add_proc(t_proc *proc, t_proc_grp *proc_grp);
int			add_null_proc(t_proc_grp *proc_grp, const char *name,
t_cmd *cmd);

#endif
