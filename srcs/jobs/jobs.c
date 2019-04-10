/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 17:32:12 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 22:44:31 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs.h"

void	list_procs(t_proc_grp *proc_grp)
{
	t_list	*tmp;
	t_proc	*proc;

	tmp = proc_grp->procs;
	while (tmp != NULL)
	{
		proc = (t_proc *)tmp->content;
		dprintf(2, " | STATUS = %d PID = %d NAME = %s",
	proc->status, proc->pid, proc->name);
		tmp = tmp->next;
	}
}

void	list_jobs()
{
	t_list	*tmp;
	t_jobs	*jobs;
	t_proc_grp	*proc_grp;

	jobs = jobs_super_get();
	tmp = jobs->proc_grps;
	while (tmp != NULL)
	{
		proc_grp = (t_proc_grp *)tmp->content;
		dprintf(2, "STATUS = %d PGID = %d NAME = %s",
	proc_grp->status, proc_grp->pgid, proc_grp->name);
		list_procs(proc_grp);
		tmp = tmp->next;
	}
}
