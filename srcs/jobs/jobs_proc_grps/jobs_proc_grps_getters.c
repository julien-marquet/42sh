/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_proc_grps_getters.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:37:51 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 19:45:18 by jmarquet    ###    #+. /#+    ###.fr     */
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
