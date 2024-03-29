/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_procs_setters.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:45:06 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 16:56:36 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_procs/jobs_procs_setters.h"

t_proc		*new_proc(int pid, const char *name, int last)
{
	t_proc	*proc;

	if ((proc = ft_memalloc(sizeof(t_proc))) == NULL)
		return (NULL);
	proc->pid = pid;
	proc->name = ft_strdup(name);
	proc->last = last;
	proc->pipe_in = -1;
	proc->pipe_out = -1;
	return (proc);
}

int			add_proc(t_proc *proc, t_proc_grp *proc_grp)
{
	t_list	*node;

	if (proc != NULL && proc_grp != NULL)
	{
		if ((node = ft_memalloc(sizeof(t_list))) == NULL)
			return (1);
		node->content_size = sizeof(proc);
		node->content = proc;
		node->next = NULL;
		ft_lstappend(&proc_grp->procs, node);
		return (0);
	}
	else
		return (1);
}

int			add_null_proc(t_proc_grp *proc_grp, const char *name,
t_cmd *cmd, int err)
{
	t_proc	*proc;

	if ((proc = new_proc(0, name, is_last(cmd))) == NULL)
		return (1);
	proc->null = 1;
	proc->status = exited;
	proc->code = 126;
	if (err == 0)
		proc->code = cmd_is_null(cmd) &&
	cmd->assign == 1 ? 0 : 127;
	add_proc(proc, proc_grp);
	return (0);
}
