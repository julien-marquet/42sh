/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_proc_grps_setters.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:43:29 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/12 21:59:35 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_proc_grps/jobs_proc_grps_setters.h"

t_proc_grp	*new_proc_grp(int pgid, const char *name)
{
	t_proc_grp	*proc_grp;

	if ((proc_grp = ft_memalloc(sizeof(t_proc_grp))) == NULL)
		return (NULL);
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
		ft_lstappend(&jobs->proc_grps, node);
		return (0);
	}
	else
		return (1);
}
