/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_procs_getters.h                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:54:34 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/20 00:41:17 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef JOBS_PROCS_GETTERS_H
# define JOBS_PROCS_GETTERS_H

# include "common.h"
# include "jobs/jobs_super.h"

t_proc		*find_by_pid(t_proc_grp *proc_grp, int pid);
t_proc		*get_last_proc(t_proc_grp *proc_grp);
t_proc		*get_last_proc_all(t_proc_grp *proc_grp);
int			pid_is_active(int pid);

#endif
