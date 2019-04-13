/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_update.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:39:53 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 03:31:40 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_update.h"

void	convert_stat_loc(int stat_loc, t_proc *proc)
{
	if (WIFEXITED(stat_loc))
	{
		proc->status = exited;
		proc->code = WEXITSTATUS(stat_loc);
	}
	else if (WIFSTOPPED(stat_loc))
		proc->status = stopped;
	else if (WIFSIGNALED(stat_loc))
	{
		proc->status = signaled;
		proc->code = WTERMSIG(stat_loc);
	}
	else if (WIFCONTINUED(stat_loc))
		proc->status = running;
}

void	update_procs(t_proc_grp *proc_grp)
{
	t_list			*tmp;
	t_proc			*proc;
	int				stat_loc;

	tmp = proc_grp->procs;
	while (tmp != NULL)
	{
		stat_loc = 0;
		proc = (t_proc *)tmp->content;
		if (waitpid(proc->pid, &stat_loc, WUNTRACED) > 0)
		{
			convert_stat_loc(stat_loc, proc);
			proc->updated = 1;
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
	if (jobs->busy == 0)
	{
		jobs->busy = 1;
		tmp = jobs->proc_grps;
		while (tmp != NULL)
		{
			proc_grp = (t_proc_grp *)tmp->content;
			update_procs(proc_grp);
			tmp = tmp->next;
		}
		jobs->busy = 0;
	}
}
