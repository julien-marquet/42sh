/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_update.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:39:53 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/12 21:40:21 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_update.h"

void	update_procs(t_proc_grp *proc_grp)
{
	t_list			*tmp;
	t_proc			*proc;
	int				stat_loc;
	t_job_status	status;

	tmp = proc_grp->procs;
	while (tmp != NULL)
	{
		proc = (t_proc *)tmp->content;
		waitpid(proc->pid, &stat_loc, WNOHANG);
		status = retrieve_status(stat_loc);
		if (status != proc->status)
		{
			proc->updated = 1;
			proc->status = status;
		}
		tmp = tmp->next;
	}
}

void	update_jobs_status()
{
	t_list	*tmp;
	t_jobs	*jobs;
	t_proc_grp	*proc_grp;

	jobs = jobs_super_get();
	tmp = jobs->proc_grps;
	while (tmp != NULL)
	{
		proc_grp = (t_proc_grp *)tmp->content;
		update_procs(proc_grp);
		tmp = tmp->next;
	}
}