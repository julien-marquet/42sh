/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_update.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:39:53 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 13:41:36 by jmarquet    ###    #+. /#+    ###.fr     */
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
				if (proc->status == stopped)
					((t_proc_grp *)tmp->content)->background = 1;
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

int		search_for_valid_condition(const char *condition, t_cmd **cmd)
{
	t_cmd	*acmd;
	int		found;

	acmd = *cmd;
	found = 0;
	while (*cmd != NULL)
	{
		if (!(*cmd)->red || ft_strcmp((*cmd)->red, ";") == 0 ||
	ft_strcmp((*cmd)->red, "&") == 0)
			break ;
		if ((*cmd)->red && ft_strcmp((*cmd)->red, condition) == 0)
		{
			found = 1;
			break ;
		}
		*cmd = (*cmd)->next;
	}
	if (found == 1 && (*cmd)->next)
	{
		*cmd = (*cmd)->next;
		free_executed_cmds(acmd, *cmd, NULL);
		return (1);
	}
	return (0);
}

void	check_revive_process_group(t_sh_state *sh_state, t_proc_grp *proc_grp,
t_proc *last_proc)
{
	int		to_revive;
	t_cmd	*acmd;

	acmd = proc_grp->remaining;
	to_revive = 0;
	if (proc_grp->last_red && ft_strcmp(proc_grp->last_red, "&&") == 0)
	{
		if (last_proc->status == exited && last_proc->code == 0)
			to_revive = 1;
		else if (search_for_valid_condition("||", &proc_grp->remaining))
			to_revive = 1;
	}
	else if (proc_grp->last_red && ft_strcmp(proc_grp->last_red, "||") == 0)
	{
		if (last_proc->status == signaled ||
	(last_proc->status == exited && last_proc->code != 0))
			to_revive = 1;
		else if (search_for_valid_condition("&&", &proc_grp->remaining))
			to_revive = 1;
	}
	if (to_revive == 1)
		revive_process_group(sh_state, proc_grp);
	else
	{
		display_job_alert(proc_grp, last_proc);
		free_cmds(proc_grp->remaining);
	}
}

void	wait_for_grp(t_sh_state *sh_state, t_proc_grp *proc_grp)
{
	t_proc	*last_proc;

	while (1)
	{
		pause();
		if ((last_proc = get_last_proc(proc_grp)) != NULL)
		{
			if (last_proc->updated == 1)
			{
				sh_state->status = get_proc_return(last_proc);
				last_proc->updated = 0;
				break ;
			}
		}
	}
}

void	handle_process_update(void)
{
	int			pid;
	int			stat_loc;
	t_jobs		*jobs;
	t_proc_grp	*proc_grp;
	t_proc		*proc;

	jobs = jobs_super_get(NULL);
	if ((pid = waitpid(WAIT_ANY, &stat_loc, WUNTRACED)) > 0)
	{
		if ((proc_grp = update_proc_status(jobs, pid,
	stat_loc)) != NULL && (proc = get_last_proc(proc_grp)) != NULL)
		{
			if (proc->updated && proc_grp->remaining == NULL &&
		proc_grp->background == 1)
				display_job_alert(proc_grp, proc);
			if (proc->status != stopped && proc->pid == pid &&
		proc_grp->remaining != NULL)
			{
				check_revive_process_group(jobs->sh_state,
				proc_grp, proc);
			}
		}
	}
}

void	jobs_set_sh_state(t_sh_state *sh_state)
{
	t_jobs	*jobs;

	jobs = jobs_super_get(sh_state);
}
