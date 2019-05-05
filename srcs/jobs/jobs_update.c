/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_update.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:39:53 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 00:00:30 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_update.h"

int			search_for_valid_condition(const char *condition, t_cmd **cmd)
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

static int	get_revive_process_group(t_proc_grp *proc_grp, t_proc *last_proc)
{
	if (proc_grp->last_red && ft_strcmp(proc_grp->last_red, "&&") == 0)
	{
		if (last_proc->status == exited && last_proc->code == 0)
			return (1);
		else if (search_for_valid_condition("||", &proc_grp->remaining))
			return (1);
	}
	else if (proc_grp->last_red && ft_strcmp(proc_grp->last_red, "||") == 0)
	{
		if (last_proc->status == signaled ||
	(last_proc->status == exited && last_proc->code != 0))
			return (1);
		else if (search_for_valid_condition("&&", &proc_grp->remaining))
			return (1);
	}
	return (0);
}

void		check_revive_process_group(t_sh_state *sh_state,
t_proc_grp *proc_grp, t_proc *last_proc)
{
	t_cmd	*acmd;

	acmd = proc_grp->remaining;
	if (get_revive_process_group(proc_grp, last_proc) == 1)
		exec_cmd_list(sh_state, proc_grp->remaining, proc_grp->name, proc_grp);
	else
	{
		if (proc_grp->background == 1)
			display_job_alert(proc_grp, last_proc);
		free_cmds(acmd);
	}
}

static void	check_child_updated(int *child_updated)
{
	if (*child_updated == 0)
		pause();
	*child_updated = 0;
}

void		wait_for_grp(t_sh_state *sh_state, t_proc_grp *proc_grp)
{
	t_proc	*last_proc;
	t_jobs	*jobs;
	int		*child_updated;

	jobs = jobs_super_get(NULL);
	child_updated = super_get_sigchld_flag();
	while (1)
	{
		check_child_updated(child_updated);
		if ((last_proc = get_last_proc_all(proc_grp)) != NULL)
		{
			if (last_proc->updated == 1)
			{
				sh_state->status = get_proc_return(last_proc);
				last_proc->updated = 0;
				if (last_proc->status != stopped && proc_grp->background == 0 &&
			proc_grp->remaining != NULL)
					check_revive_process_group(jobs->sh_state,
					proc_grp, last_proc);
				break ;
			}
		}
		else
			break ;
	}
}
