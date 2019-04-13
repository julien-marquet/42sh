/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_update.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:39:53 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 21:22:59 by jmarquet    ###    #+. /#+    ###.fr     */
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

void	update_proc_status(t_jobs *jobs, int pid, int stat_loc)
{
	t_list		*tmp;
	t_list		*procs_list;
	t_proc		*proc;

	tmp = jobs->proc_grps;
	while (tmp != NULL)
	{
		procs_list = ((t_proc_grp *)tmp->content)->procs;
		while (procs_list != NULL)
		{
			proc = (t_proc *)procs_list->content;
			if (proc->pid == pid)
			{
				convert_stat_loc(stat_loc, proc);
				proc->updated = 1;
			}
			procs_list = procs_list->next;
		}
		tmp = tmp->next;
	}
}

void	update_jobs_status(int wanted)
{
	int		pid;
	int		stat_loc;
	t_jobs	*jobs;

	jobs = jobs_super_get();
	if (jobs->busy == 0)
	{
		jobs->busy = 1;
		while ((pid = waitpid(WAIT_ANY, &stat_loc, WUNTRACED)) > 0)
		{
			update_proc_status(jobs, pid, stat_loc);
			if (wanted == pid || wanted <= 0)
				break ;
		}
		jobs->busy = 0;
	}
}
