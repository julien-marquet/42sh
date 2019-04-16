/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_update.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:39:53 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 19:53:05 by jmarquet    ###    #+. /#+    ###.fr     */
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

void	revive_process_group(t_sh_state *sh_state, t_proc_grp *proc_grp)
{
	dprintf(2, "proc_grp remaining = %d\n", proc_grp->remaining != NULL);
	dprintf(2, "startinf from %s\n", proc_grp->remaining->str);
	exec_cmd_list(sh_state, proc_grp->remaining, proc_grp->name);
}

void	check_revive_process_group(t_sh_state *sh_state, t_proc_grp *proc_grp, t_proc *last_proc)
{
	int		to_revive;

	dprintf(2, "checking for revive\n");
	dprintf(2, "last red = %s\n", proc_grp->last_red);
	dprintf(2, "status = %d, code = %d\n", last_proc->status, last_proc->code);
	to_revive = 0;
	if (last_proc->status == exited && last_proc->code == 0)
	{
		if (ft_strcmp(proc_grp->last_red, "&&") == 0)
			to_revive = 1;
	}
	else if (last_proc->status == signaled || last_proc->status == exited)
	{
		if (ft_strcmp(proc_grp->last_red, "||") == 0)
			to_revive = 1;
	}
	if (to_revive == 1)
	{
		dprintf(2, "revive the process group %s\n", proc_grp->name);
		revive_process_group(sh_state, proc_grp);
	}
}

void	handle_process_update(int wanted)
{
	int			pid;
	int			stat_loc;
	t_jobs		*jobs;
	t_proc_grp	*proc_grp;
	t_proc		*proc;

	jobs = jobs_super_get(NULL);
	if (jobs->busy == 0)
	{
		while ((pid = waitpid(WAIT_ANY, &stat_loc, WUNTRACED)) > 0)
		{
			if ((proc_grp = update_proc_status(jobs, pid, stat_loc)) != NULL)
			{
				if ((proc = get_last_proc(proc_grp)) != NULL &&
			proc->pid == pid && proc_grp->remaining != NULL)
					check_revive_process_group(jobs->sh_state, proc_grp, proc);
			}
			if (wanted == pid || wanted <= 0)
				break ;
		}
		jobs->busy = 0;
	}
}

void	jobs_set_sh_state(t_sh_state *sh_state)
{
	t_jobs	*jobs;

	jobs = jobs_super_get(sh_state);
}