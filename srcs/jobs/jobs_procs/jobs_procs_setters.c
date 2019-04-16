/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_procs_setters.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:45:06 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 02:23:24 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_procs/jobs_procs_setters.h"

t_proc	*new_proc(int pid, const char *name, int last, t_cmd *remaining)
{
	t_proc	*proc;

	if ((proc = ft_memalloc(sizeof(t_proc))) == NULL)
		return (NULL);
	proc->pid = pid;
	proc->remaining = remaining;
	proc->name = ft_strdup(name);
	proc->last = last;
	return (proc);
}

int			add_proc(t_proc *proc, t_proc_grp *proc_grp)
{
	t_list	*node;

	if (proc != NULL && proc_grp != NULL)
	{
		if ((node = ft_lstnew(proc, sizeof(t_proc))) == NULL)
			return (1);
		ft_lstappend(&proc_grp->procs, node);
		return (0);
	}
	else
		return (1);
}
