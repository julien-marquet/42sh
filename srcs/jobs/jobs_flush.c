/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_flush.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:24:59 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 02:53:53 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_flush.h"

static void	remove_node_proc_grp(t_list **prev, t_list **tmp, t_jobs *jobs)
{
	t_proc_grp	*proc_grp;

	if (*prev == NULL)
		jobs->proc_grps = (*tmp)->next;
	else
		(*prev)->next = (*tmp)->next;
	proc_grp = (t_proc_grp *)(*tmp)->content;
	ft_strdel(&proc_grp->name);
	ft_strdel(&proc_grp->last_red);
	free(proc_grp);
	free(*tmp);
	*tmp = *prev;
}

static int	has_to_be_flushed(t_proc *last_proc, t_proc *last_proc_all,
t_proc_grp *proc_grp)
{
	if (last_proc == NULL)
	{
		if (last_proc_all == NULL)
			return (0);
		return (1);
	}
	else
	{
		return (proc_grp->revived == 1 || last_proc->status == exited ||
	last_proc->status == signaled);
	}
}

static void	flush_procs(t_proc_grp *proc_grp)
{
	t_list			*tmp;
	t_list			*bfree;
	t_proc			*last_proc;
	t_proc			*last_proc_all;
	t_proc			*proc;

	last_proc_all = get_last_proc_all(proc_grp);
	last_proc = get_last_proc(proc_grp);
	if (has_to_be_flushed(last_proc, last_proc_all, proc_grp))
	{
		tmp = proc_grp->procs;
		while (tmp != NULL)
		{
			bfree = tmp->next;
			proc = (t_proc *)tmp->content;
			ft_strdel(&proc->name);
			free(proc);
			tmp->content = NULL;
			free(tmp);
			tmp = NULL;
			tmp = bfree;
		}
		proc_grp->procs = NULL;
	}
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
		{
			dprintf(2, "flush proc_grp");
			remove_node_proc_grp(&prev, &tmp, jobs);
		}
		if (tmp != NULL)
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}
