/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 17:29:57 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/21 03:27:56 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef JOBS_H
# define JOBS_H

# include "jobs/jobs_procs/jobs_procs.h"
# include "jobs/jobs_proc_grps/jobs_proc_grps.h"
# include "jobs/jobs_controls.h"
# include "jobs/jobs_flush.h"
# include "jobs/jobs_display.h"
# include "jobs/jobs_update.h"
# include "jobs/jobs_printers.h"
# include "common.h"

void	list_jobs();
void	update_jobs_status();
void	display_jobs_alert();

#endif
