/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_flush.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:24:59 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 19:45:18 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_flush.h"

static void	remove_node_proc(t_list **prev, t_list **tmp, t_proc_grp *proc_grp)
{
	if (*prev == NULL)
		proc_grp->procs = (*tmp)->next;
	else
		(*prev)->next = (*tmp)->next;
	free((t_proc *)(*tmp)->content);
	free(*tmp);
	*tmp = *prev;
}

static void	remove_node_proc_grp(t_list **prev, t_list **tmp, t_jobs *jobs)
{
	if (*prev == NULL)
		jobs->proc_grps = (*tmp)->next;
	else
		(*prev)->next = (*tmp)->next;
	free((t_proc_grp *)(*tmp)->content);
	free(*tmp);
	*tmp = *prev;
}

static int	flush_procs(t_proc_grp *proc_grp)
{
	t_list			*tmp;
	t_job_status	status;
	t_list			*prev;

	status = -1;
	prev = NULL;
	tmp = proc_grp->procs;
	while (tmp != NULL)
	{
		status = ((t_proc *)tmp->content)->status;
		if (status == exited || status == signaled)
			remove_node_proc(&prev, &tmp, proc_grp);
		if (tmp != NULL)
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
	return (status);
}

void		flush_exited(void)
{
	t_list		*tmp;
	t_jobs		*jobs;
	t_proc_grp	*proc_grp;
	t_list		*prev;

	jobs = jobs_super_get(NULL);
	prev = NULL;
	tmp = jobs->proc_grps;
	while (tmp != NULL)
	{
		proc_grp = (t_proc_grp *)tmp->content;
		flush_procs(proc_grp);
		if (proc_grp->procs == NULL)
			remove_node_proc_grp(&prev, &tmp, jobs);
		if (tmp != NULL)
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}
