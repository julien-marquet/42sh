/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_proc_grps_getters.h                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:52:17 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 16:04:37 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef JOBS_PROC_GRPS_GETTERS_H
# define JOBS_PROC_GRPS_GETTERS_H

# include "common.h"
# include "jobs/jobs_procs/jobs_procs.h"
# include "jobs/jobs_super.h"

t_proc_grp		*find_by_gpid(int pgid);
t_proc_grp		*find_active_proc_grp_by_name(const char *name, int *nres);
t_proc_grp		*find_active_proc_grp_by_needle(const char *name, int *nres);
t_proc_grp		*find_proc_grp_by_name(const char *name, int *nres);
t_proc_grp		*get_first_proc_grp();
t_proc_grp		*get_first_active_proc_grp();
unsigned char	retrieve_proc_grp_res(t_proc_grp *proc_grp);
int				count_true_procs(t_proc_grp *proc_grp);
t_proc_grp		*find_active_proc_grp_by_num(int num);
int				get_active_proc_grp_nb(void);
int				get_displayable_proc_grp_nb(void);
unsigned char	get_proc_return(t_proc *proc);

#endif
