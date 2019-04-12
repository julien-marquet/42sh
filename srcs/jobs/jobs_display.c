/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_display.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:41:11 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/12 21:41:44 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_display.h"

void	print_job_status(t_proc_grp *proc_grp, t_job_status status)
{
	dprintf(1, "JOBS %s, STATUS %d\n", proc_grp->name, status);
}

void	display_jobs_alert()
{
	t_list			*tmp;
	t_jobs			*jobs;
	t_proc_grp		*proc_grp;
	int				status;
	t_list			*prev;

	prev = NULL;
	jobs = jobs_super_get();
	tmp = jobs->proc_grps;
	while (tmp != NULL)
	{
		proc_grp = (t_proc_grp *)tmp->content;
		if ((status = get_proc_grp_status(proc_grp)) != -1)
			print_job_status(proc_grp, status);
		if (status == exited)
		{
			if (prev == NULL)
				jobs->proc_grps = tmp->next;
			else
				prev->next = tmp->next;
			free(proc_grp);
			free(tmp);
			tmp = prev;
		}
		if (tmp != NULL)
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

void	list_procs(t_proc_grp *proc_grp)
{
	t_list	*tmp;
	t_proc	*proc;

	tmp = proc_grp->procs;
	while (tmp != NULL)
	{
		proc = (t_proc *)tmp->content;
		dprintf(2, " | STATUS = %d PID = %d NAME = %s UPDATED = %d\n",
	proc->status, proc->pid, proc->name, proc->updated);
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
		dprintf(1, "PGID = %d NAME = %s\n", proc_grp->pgid, proc_grp->name);
		list_procs(proc_grp);
		tmp = tmp->next;
	}
}