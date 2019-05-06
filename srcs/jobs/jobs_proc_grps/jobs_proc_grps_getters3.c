/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_proc_grps_getters3.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 22:34:16 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 22:34:17 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_proc_grps/jobs_proc_grps_getters.h"

t_proc_grp	*find_active_proc_grp_by_name(const char *name, int *nres)
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
		if (ft_strcmp(((t_proc_grp *)tmp->content)->name, name) == 0 &&
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
