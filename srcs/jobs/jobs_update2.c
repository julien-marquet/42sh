/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_update2.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 23:08:11 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 23:08:12 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_update.h"

void		convert_stat_loc(int stat_loc, t_proc *proc)
{
	if (WIFEXITED(stat_loc))
	{
		proc->status = exited;
		proc->code = WEXITSTATUS(stat_loc);
	}
	else if (WIFCONTINUED(stat_loc))
		proc->status = running;
	else if (WIFSTOPPED(stat_loc))
	{
		proc->status = stopped;
		proc->code = WSTOPSIG(stat_loc);
	}
	else if (WIFSIGNALED(stat_loc))
	{
		proc->status = signaled;
		proc->code = WTERMSIG(stat_loc);
	}
}

t_proc_grp	*update_proc_status(t_jobs *jobs, int pid, int stat_loc)
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
				return ((t_proc_grp *)tmp->content);
			}
			procs_list = procs_list->next;
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static void	check_state(t_proc *proc, t_proc_grp *proc_grp,
int pid, t_sh_state *state)
{
	if (proc->status == stopped)
		proc_grp->background = 1;
	if (proc->updated)
	{
		if (proc_grp->background == 1)
		{
			if (proc_grp->remaining == NULL &&
		(proc->pid == pid || proc->null == 1))
				display_job_alert(proc_grp, proc);
		}
		else if (proc->pid == pid && proc->status == signaled &&
	proc->code != 2)
		{
			ft_putstr("Signaled: ");
			ft_putnbr(proc->code);
			ft_putstr("\n");
		}
	}
	if (proc->status != stopped && proc->pid == pid &&
proc_grp->remaining != NULL && proc_grp->background == 1)
		check_revive_process_group(state, proc_grp, proc);
}

void		treate_process(int *child_updated, int pid, int stat_loc)
{
	t_proc		*proc;
	t_proc_grp	*proc_grp;
	int			background_init;

	if ((proc_grp = update_proc_status(jobs_super_get(NULL), pid,
stat_loc)) != NULL && (proc = get_last_proc_all(proc_grp)) != NULL)
	{
		background_init = proc_grp->background;
		check_state(proc, proc_grp, pid, jobs_super_get(NULL)->sh_state);
		if (background_init == 0)
			*child_updated = 1;
	}
}

void		handle_process_update(void)
{
	int			pid;
	int			stat_loc;

	if ((pid = waitpid(WAIT_ANY, &stat_loc, WUNTRACED)) > 0)
		treate_process(super_get_sigchld_flag(), pid, stat_loc);
}
