/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_flush.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:23:51 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 03:22:05 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef JOBS_FLUSH_H
# define JOBS_FLUSH_H

# include "common.h"
# include "jobs/jobs_super.h"
# include "jobs/jobs_procs/jobs_procs_getters.h"

void	flush_exited();
void	flush_all_jobs();

int		has_to_be_flushed(t_proc *last_proc, t_proc *last_proc_all,
t_proc_grp *proc_grp);

#endif
