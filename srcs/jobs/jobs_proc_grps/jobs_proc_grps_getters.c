/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_proc_grps_getters.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:37:51 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 17:00:51 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_proc_grps/jobs_proc_grps_getters.h"

t_proc_grp		*get_first_proc_grp(void)
{
	t_list		*tmp;
	t_jobs		*jobs;
	t_proc_grp	*proc_grp;

	proc_grp = NULL;
	jobs = jobs_super_get(NULL);
	tmp = jobs->proc_grps;
	if (tmp != NULL)
		proc_grp = (t_proc_grp *)tmp->content;
	return (proc_grp);
}

t_proc_grp		*get_first_active_proc_grp(void)
{
	t_list		*tmp;
	t_jobs		*jobs;
	t_proc_grp	*proc_grp;
	t_proc		*proc;

	proc_grp = NULL;
	jobs = jobs_super_get(NULL);
	tmp = jobs->proc_grps;
	while (tmp != NULL)
	{
		proc_grp = (t_proc_grp *)tmp->content;
		if ((proc = get_last_proc(proc_grp)) != NULL && proc->status != exited)
			return (proc_grp);
		tmp = tmp->next;
	}
	return (NULL);
}

unsigned char	get_proc_return(t_proc *proc)
{
	unsigned char res;

	res = 0;
	if (proc->status == exited)
		res = proc->code;
	else if (proc->status == stopped)
		res = 146;
	else if (proc->status == signaled)
		res = 128 + proc->code;
	return (res);
}

unsigned char	retrieve_proc_grp_res(t_proc_grp *proc_grp)
{
	t_list			*tmp;
	t_proc			*proc;

	tmp = proc_grp->procs;
	proc = NULL;
	while (tmp != NULL)
	{
		proc = (t_proc *)tmp->content;
		tmp = tmp->next;
	}
	if (proc != NULL)
		return (get_proc_return(proc));
	return (0);
}

int				count_true_procs(t_proc_grp *proc_grp)
{
	t_list			*tmp;
	t_proc			*proc;
	int				res;

	tmp = proc_grp->procs;
	proc = NULL;
	res = 0;
	while (tmp != NULL)
	{
		proc = (t_proc *)tmp->content;
		if (proc->null == 0)
			res++;
		tmp = tmp->next;
	}
	return (res);
}
