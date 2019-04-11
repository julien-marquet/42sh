/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_proc.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 21:13:55 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 02:36:01 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_proc.h"

t_proc		*find_by_pid(t_proc_grp *proc_grp, int pid)
{
	t_list	*tmp;

	tmp = proc_grp->procs;
	while (tmp != NULL)
	{
		if (((t_proc *)tmp->content)->pid == pid)
			return ((t_proc *)tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

t_proc	*new_proc(int pid, t_job_status status, const char *name)
{
	t_proc	*proc;

	if ((proc = ft_memalloc(sizeof(t_proc))) == NULL)
		return (NULL);
	proc->pid = pid;
	proc->status = status;
	proc->name = ft_strdup(name);
	return (proc);
}

int			add_proc(t_proc *proc, t_proc_grp *proc_grp)
{
	t_list	*node;

	if (proc != NULL && proc_grp != NULL)
	{
		if ((node = ft_lstnew(proc, sizeof(t_proc))) == NULL)
			return (1);
		ft_lstprepend(&proc_grp->procs, node);
		return (0);
	}
	else
		return (1);
}
