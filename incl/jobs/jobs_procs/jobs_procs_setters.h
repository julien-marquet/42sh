/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_procs_setters.h                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:55:02 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 00:50:18 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef JOBS_PROCS_SETTERS_H
# define JOBS_PROCS_SETTERS_H

# include "common.h"

t_proc		*new_proc(int pid, t_job_status status, const char *name, int last);
int			add_proc(t_proc *proc, t_proc_grp *proc_grp);

#endif
