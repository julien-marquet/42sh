/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_procs_setters.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:45:06 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 22:32:39 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_procs/jobs_procs_setters.h"

t_proc	*new_proc(int pid, const char *name, int last)
{
	t_proc	*proc;

	if ((proc = ft_memalloc(sizeof(t_proc))) == NULL)
		return (NULL);
	proc->pid = pid;
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

int		add_null_proc(t_proc_grp *proc_grp, const char *name, int last)
{
	t_proc	*proc;

	if ((proc = new_proc(0, name, last)) == NULL)
		return (1);
	proc->null = 1;
	add_proc(proc, proc_grp);
	return (0);
}
