/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_proc_grps_getters.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:37:51 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 00:07:08 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_proc_grps/jobs_proc_grps_getters.h"

t_proc_grp	*find_by_gpid(int pgid)
{
	t_list	*tmp;
	t_jobs	*jobs;

	jobs = jobs_super_get(NULL);
	tmp = jobs->proc_grps;
	while (tmp != NULL)
	{
		if (((t_proc_grp *)tmp->content)->pgid == pgid)
			return ((t_proc_grp *)tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

t_proc_grp	*find_active_proc_grp_by_name(const char *name, int *nres)
{
	t_list		*tmp;
	t_jobs		*jobs;
	t_proc_grp	*proc_grp;

	*nres = 0;
	proc_grp = NULL;
	jobs = jobs_super_get(NULL);
	tmp = jobs->proc_grps;
	while (tmp != NULL)
	{
		if (ft_strcmp(((t_proc_grp *)tmp->content)->name, name) == 0 &&
	get_last_proc(((t_proc_grp *)tmp->content))->status != exited)
		{
			(*nres)++;
			proc_grp = (t_proc_grp *)tmp->content;
		}
		tmp = tmp->next;
	}
	return (*nres > 1 ? NULL : proc_grp);
}

t_proc_grp	*find_proc_grp_by_name(const char *name, int *nres)
{
	t_list		*tmp;
	t_jobs		*jobs;
	t_proc_grp	*proc_grp;

	*nres = 0;
	proc_grp = NULL;
	jobs = jobs_super_get(NULL);
	tmp = jobs->proc_grps;
	while (tmp != NULL)
	{
		if (ft_strcmp(((t_proc_grp *)tmp->content)->name, name) == 0)
		{
			(*nres)++;
			proc_grp = (t_proc_grp *)tmp->content;
		}
		tmp = tmp->next;
	}
	return (*nres > 1 ? NULL : proc_grp);
}

t_proc_grp	*get_first_proc_grp()
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

t_proc_grp	*get_first_active_proc_grp()
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

static unsigned char	get_proc_return(t_proc *proc)
{
	unsigned char res;

	res = 0;
	if (proc->null)
	{
		if (proc->not_found == 1)
			res = 127;
		else if (proc->no_permission == 1)
			res = 126;
		else if (proc->assign == 1)
			res = 0;
	}
	else if (proc->status == exited)
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
