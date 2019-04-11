/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 17:32:12 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 20:50:43 by jmarquet    ###    #+. /#+    ###.fr     */
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
		dprintf(2, " | STATUS = %d PID = %d NAME = %s UPDATED = %d\n",
	proc->status, proc->pid, proc->name, proc->updated);
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
		dprintf(1, "PGID = %d NAME = %s\n", proc_grp->pgid, proc_grp->name);
		list_procs(proc_grp);
		tmp = tmp->next;
	}
}

t_job_status	retrieve_status(int stat_loc)
{

	if (WIFEXITED(stat_loc))
		return (exited);
	if (WIFSIGNALED(stat_loc))
		return (signaled);
	if (WIFSTOPPED(stat_loc))
		return (stopped);
	if (WIFCONTINUED(stat_loc))
		return (running);
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
			proc->updated = 1;
			// set updated flag to print afterward
			proc->status = status;
		}
		tmp = tmp->next;
	}
}

void	update_jobs_status()
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
		tmp = tmp->next;
	}
}

int		get_proc_grp_status(t_proc_grp *proc_grp)
{
	t_list			*tmp;
	t_proc			*proc;
	t_job_status	status;
	t_list			*prev;

	status = -1;
	prev = NULL;
	tmp = proc_grp->procs;
	while (tmp != NULL)
	{
		proc = (t_proc *)tmp->content;
		if (proc->updated == 1)
		{
			if ((status = proc->status) == exited)
			{
				if (prev == NULL)
					proc_grp->procs = tmp->next;
				else
					prev->next = tmp->next;
				free(proc);
				free(tmp);
				tmp = prev;
			}
		}
		if (tmp != NULL)
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
	return (status);
}

void	print_job_status(t_proc_grp *proc_grp, t_job_status status)
{
	dprintf(1, "JOBS %s, STATUS %d\n", proc_grp->name, status);
}

void	display_jobs_alert()
{
	t_list			*tmp;
	t_jobs			*jobs;
	t_proc_grp		*proc_grp;
	int				status;
	t_list			*prev;

	prev = NULL;
	jobs = jobs_super_get();
	tmp = jobs->proc_grps;
	while (tmp != NULL)
	{
		proc_grp = (t_proc_grp *)tmp->content;
		if ((status = get_proc_grp_status(proc_grp)) != -1)
				print_job_status(proc_grp, status);
		if (status == exited)
		{
			if (prev == NULL)
				jobs->proc_grps = tmp->next;
			else
				prev->next = tmp->next;
			free(proc_grp);
			free(tmp);
			tmp = prev;
		}
		if (tmp != NULL)
		{
			prev = tmp;
			tmp = tmp->next;
		}
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