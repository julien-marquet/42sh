/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 17:29:57 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 18:48:02 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef JOBS_H
# define JOBS_H

# include "jobs/jobs_proc.h"
# include "jobs/jobs_proc_grp.h"
# include "common.h"

void	list_jobs();
void	update_jobs_status();
void	display_jobs_alert();

#endif
