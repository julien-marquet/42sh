/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_update.h                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:57:17 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 15:04:25 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef JOBS_UPDATE_H
# define JOBS_UPDATE_H

# include "common.h"
# include "jobs/jobs_super.h"
# include "jobs/jobs_procs/jobs_procs.h"
# include "exec/exec.h"
# include "jobs/child_updated_flag.h"

void		convert_stat_loc(int stat_loc, t_proc *proc);
t_proc_grp	*update_proc_status(t_jobs *jobs, int pid, int stat_loc);
void		update_jobs_status(int wanted);
void		handle_process_update(void);
void		wait_for_grp(t_sh_state *sh_state, t_proc_grp *proc_grp);
void		check_revive_process_group(t_sh_state *sh_state, t_proc_grp *proc_grp,
t_proc *last_proc);

#endif
