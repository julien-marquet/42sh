/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_proc_grps_getters.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:37:51 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 12:30:50 by jmarquet    ###    #+. /#+    ###.fr     */
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
	proc->status != exited)
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
	while (tmp != NULL && index <= num)
	{
		if ((proc = get_last_proc(((t_proc_grp *)tmp->content))) != NULL &&
	proc->status != exited)
		{
			if (total - index == num)
				return ((t_proc_grp *)tmp->content);
			index++;
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
