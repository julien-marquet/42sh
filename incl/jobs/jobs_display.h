/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_display.h                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:56:41 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 20:20:02 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef JOBS_DISPLAY_H
# define JOBS_DISPLAY_H

# include "common.h"
# include "jobs/jobs_procs/jobs_procs.h"
# include "jobs/jobs_super.h"
# include "jobs/jobs_printers.h"

void	display_last_bpgid(int bpid, t_proc_grp *proc_grp);
void	display_job_alert(t_proc_grp *proc_grp, t_proc *last_proc);
void	jobs_handle_display(int mode, const char *search, const char *origin);

#endif
