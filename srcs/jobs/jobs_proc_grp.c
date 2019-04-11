/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_proc_grp.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 21:18:00 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 02:00:54 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_proc_grp.h"

t_proc_grp	*find_by_gpid(int pgid)
{
	t_list	*tmp;
	t_jobs	*jobs;

	jobs = jobs_super_get();
	tmp = jobs->proc_grps;
	while (tmp != NULL)
	{
		if (((t_proc_grp *)tmp->content)->pgid == pgid)
			return ((t_proc_grp *)tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

t_proc_grp	*new_proc_grp(int pgid, int status, const char *name)
{
	t_proc_grp	*proc_grp;

	if ((proc_grp = ft_memalloc(sizeof(t_proc_grp))) == NULL)
		return (NULL);
	proc_grp->procs = NULL;
	proc_grp->status = status;
	proc_grp->pgid = pgid;
	proc_grp->name = ft_strdup(name);
	return (proc_grp);
}

int			add_proc_grp(t_proc_grp *proc_grp)
{
	t_list	*node;
	t_jobs	*jobs;

	if (proc_grp != NULL)
	{
		if ((node = ft_memalloc(sizeof(t_list))) == NULL)
			return (1);
		jobs = jobs_super_get();
		node->content_size = sizeof(t_proc_grp);
		node->content = proc_grp;
		node->next = NULL;
		ft_lstprepend(&jobs->proc_grps, node);
		return (0);
	}
	else
		return (1);
}
