/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_proc_grps_getters2.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 22:31:07 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 22:31:09 by legrivel    ###    #+. /#+    ###.fr     */
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

int			get_displayable_proc_grp_nb(void)
{
	t_list		*tmp;
	t_jobs		*jobs;
	int			cpt;
	t_proc		*proc;

	cpt = 0;
	jobs = jobs_super_get(NULL);
	tmp = jobs->proc_grps;
	while (tmp != NULL)
	{
		if ((proc = get_last_proc(((t_proc_grp *)tmp->content))) != NULL)
			cpt++;
		tmp = tmp->next;
	}
	return (cpt);
}

int			get_active_proc_grp_nb(void)
{
	t_list		*tmp;
	t_jobs		*jobs;
	int			cpt;
	t_proc		*proc;

	cpt = 0;
	jobs = jobs_super_get(NULL);
	tmp = jobs->proc_grps;
	while (tmp != NULL)
	{
		if ((proc = get_last_proc(((t_proc_grp *)tmp->content))) != NULL &&
	proc->status != exited && proc->status != signaled)
			cpt++;
		tmp = tmp->next;
	}
	return (cpt);
}

t_proc_grp	*find_active_proc_grp_by_num(int num)
{
	t_list		*tmp;
	t_jobs		*jobs;
	int			index;
	t_proc		*proc;
	int			total;

	index = 0;
	jobs = jobs_super_get(NULL);
	tmp = jobs->proc_grps;
	total = get_active_proc_grp_nb();
	while (tmp != NULL)
	{
		if ((proc = get_last_proc_all(((t_proc_grp *)tmp->content))) != NULL)
		{
			if (proc->status != exited && proc->status != signaled)
			{
				if (total - index == num)
					return ((t_proc_grp *)tmp->content);
				index++;
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_proc_grp	*find_active_proc_grp_by_needle(const char *name, int *nres)
{
	t_list		*tmp;
	t_jobs		*jobs;
	t_proc_grp	*proc_grp;
	t_proc		*proc;

	*nres = 0;
	proc_grp = NULL;
	jobs = jobs_super_get(NULL);
	tmp = jobs->proc_grps;
	while (tmp != NULL)
	{
		if (ft_strstr(((t_proc_grp *)tmp->content)->name, name) != NULL &&
	(proc = get_last_proc(((t_proc_grp *)tmp->content))) != NULL &&
	proc->status != exited)
		{
			(*nres)++;
			proc_grp = (t_proc_grp *)tmp->content;
		}
		tmp = tmp->next;
	}
	return (*nres > 1 ? NULL : proc_grp);
}
