/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_proc_grp.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 21:19:17 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 00:59:23 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef JOBS_PROC_GRP_H
# define JOBS_PROC_GRP_H

# include "common.h"
# include "jobs/jobs_super.h"

t_proc_grp	*find_by_gpid(int pgid);
t_proc_grp	*new_proc_grp(int pgid, int status, const char *name);
int			add_proc_grp(t_proc_grp *proc_grp);

#endif
