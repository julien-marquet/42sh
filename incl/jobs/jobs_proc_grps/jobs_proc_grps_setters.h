/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_proc_grps_setters.h                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:53:36 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/12 22:27:52 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef JOBS_PROC_GRPS_SETTERS_H
# define JOBS_PROC_GRPS_SETTERS_H

# include "common.h"
# include "jobs/jobs_super.h"

t_proc_grp	*new_proc_grp(int pgid, const char *name);
int			add_proc_grp(t_proc_grp *proc_grp);

#endif
