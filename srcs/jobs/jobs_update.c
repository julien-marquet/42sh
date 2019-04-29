/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_update.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:39:53 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 18:06:44 by jmarquet    ###    #+. /#+    ###.fr     */
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
	exec_cmd_list(sh_state, proc_grp->remaining, proc_grp->name, proc_grp);
}

void	check_revive_process_group(t_sh_state *sh_state, t_proc_grp *proc_grp,
t_proc *last_proc)
{
	int		to_revive;

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
		revive_process_group(sh_state, proc_grp);
}

void	handle_process_update(int wanted)
{
	int			pid;
	int			stat_loc;
	t_jobs		*jobs;
	t_proc_grp	*proc_grp;
	t_proc		*proc;
	static int			sigcpt = 0;

	if (wanted == -1)
		sigcpt--;
	jobs = jobs_super_get(NULL);
	proc = NULL;
	if ((wanted != -1 || sigcpt < 0) && jobs->busy == 0)
	{
		jobs->busy = 1;
		while (1)
		{
			sigcpt++;
			pid = waitpid(WAIT_ANY, &stat_loc, WUNTRACED);
			if (pid <= 0 || wanted == pid || wanted <= 0)
				jobs->busy = 0;
			if (pid > 0)
			{
				if ((proc_grp = update_proc_status(jobs, pid,
			stat_loc)) != NULL)
				{
					if ((proc = get_last_proc(proc_grp)) != NULL)
					{
						if (wanted == pid)
							jobs->sh_state->status = get_proc_return(proc);
						if (proc->status != stopped && proc->pid == pid && proc_grp->remaining != NULL)
						{
							check_revive_process_group(jobs->sh_state,
							proc_grp, proc);
						}
					}
				}
				if (wanted == pid && proc == NULL)
					jobs->sh_state->status = retrieve_proc_grp_res(proc_grp);
			}
			if (pid <= 0 || wanted == pid || wanted <= 0)
				break ;
		}
	}
}

void	jobs_set_sh_state(t_sh_state *sh_state)
{
	t_jobs	*jobs;

	jobs = jobs_super_get(sh_state);
}
