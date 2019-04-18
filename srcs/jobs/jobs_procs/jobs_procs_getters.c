/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_procs_getters.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:46:10 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 00:54:33 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_procs/jobs_procs_getters.h"

t_proc		*find_by_pid(t_proc_grp *proc_grp, int pid)
{
	t_list	*tmp;

	tmp = proc_grp->procs;
	while (tmp != NULL)
	{
		if (((t_proc *)tmp->content)->pid == pid)
			return ((t_proc *)tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

t_proc *get_last_proc(t_proc_grp *proc_grp)
{
	t_list	*tmp;
	t_proc	*proc;
	t_proc	*last_full_proc;

	last_full_proc = NULL;
	proc = NULL;
	tmp = proc_grp->procs;
	while (tmp)
	{
		proc = (t_proc *)tmp->content;
		if (proc && proc->null != 1)
			last_full_proc = proc;
		tmp = tmp->next;
	}
	if (proc == NULL || proc->last == 0)
		return (NULL);
	else
		return (last_full_proc);
}

t_proc *get_last_proc_all(t_proc_grp *proc_grp)
{
	t_list	*tmp;
	t_proc	*proc;

	proc = NULL;
	tmp = proc_grp->procs;
	while (tmp)
	{
		proc = (t_proc *)tmp->content;
		tmp = tmp->next;
	}
	if (proc == NULL || proc->last == 0)
		return (NULL);
	else
		return (proc);
}