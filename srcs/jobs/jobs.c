/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 17:32:12 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 02:43:33 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs.h"

void	list_procs(t_proc_grp *proc_grp)
{
	t_list	*tmp;
	t_proc	*proc;

	tmp = proc_grp->procs;
	while (tmp != NULL)
	{
		proc = (t_proc *)tmp->content;
		dprintf(2, " | STATUS = %d PID = %d NAME = %s\n",
	proc->status, proc->pid, proc->name);
		tmp = tmp->next;
	}
}

void	list_jobs()
{
	t_list	*tmp;
	t_jobs	*jobs;
	t_proc_grp	*proc_grp;

	jobs = jobs_super_get();
	tmp = jobs->proc_grps;
	while (tmp != NULL)
	{
		proc_grp = (t_proc_grp *)tmp->content;
		dprintf(2, "PGID = %d NAME = %s\n", proc_grp->pgid, proc_grp->name);
		list_procs(proc_grp);
		tmp = tmp->next;
	}
}



t_job_status	retrieve_status(int stat_loc)
{
	if (WIFEXITED(stat_loc))
		return (1);
	return (0);
}

void	update_procs(t_proc_grp *proc_grp)
{
	t_list			*tmp;
	t_proc			*proc;
	int				stat_loc;
	t_job_status	status;

	tmp = proc_grp->procs;
	while (tmp != NULL)
	{
		proc = (t_proc *)tmp->content;
		waitpid(proc->pid, &stat_loc, WNOHANG);
		status = retrieve_status(stat_loc);
		if (status != proc->status)
		{
			// set updated flag to print afterward
			proc->status = status;
		}
		tmp = tmp->next;
	}
}

void	update_jobs_list()
{
	t_list	*tmp;
	t_jobs	*jobs;
	t_proc_grp	*proc_grp;

	jobs = jobs_super_get();
	tmp = jobs->proc_grps;
	while (tmp != NULL)
	{
		proc_grp = (t_proc_grp *)tmp->content;
		update_procs(proc_grp);
		/*if (proc_grp->procs == NULL)
			remove_proc_grp();*/
		tmp = tmp->next;
	}
}
/*
WIFEXITED(*statusPtr)
evaluates to a nonzero (true) value if the specified process terminated normally.
WEXITSTATUS(*statusPtr)
if the specified process terminated normally, this macro evaluates the lower 8 bits \
of the value passed to the exit or _exit function or returned from main.
WIFSIGNALED(*statusPtr)
evaluates to a nonzero (true) value if the specified process terminated because of an \
unhandled signal.
WTERMSIG(*statusPtr)
if the specified process is ended by an unhandled signal, this macro evaluates to the \
number of that signal.
WIFSTIPPED(*statusPtr)
evaluates to a nonzero (true) value if the specified process is currently stopped but not \
terminated.
WSTOPSIG(*statusPtr)
if the specified process is currently stopped but not terminated, then this macro evaluates \
to the number of the signal that caused the process to stop*/