/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_controls.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:42:35 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 12:57:16 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_controls.h"

void		wake_all_processes(t_proc_grp *proc_grp)
{
	t_list	*tmp;
	t_proc	*proc;

	tmp = proc_grp->procs;
	while (tmp != NULL)
	{
		proc = (t_proc *)tmp->content;
		kill(proc->pid, SIGCONT);
		proc->status = running;
		tmp = tmp->next;
	}
}

int			send_to_fg(t_sh_state *sh_state, t_proc_grp *proc_grp)
{
	int		stat_loc;
	t_proc	*last_proc;

	stat_loc = 0;
	last_proc = get_last_proc(proc_grp);
	if (last_proc)
	{
		set_term_state_backup(sh_state);
		tcsetpgrp(0, proc_grp->pgid);
		wake_all_processes(proc_grp);
		wait_for_grp(sh_state, proc_grp);
		tcsetpgrp(0, sh_state->shell_pid);
		set_term_state(sh_state);
		return (0);
	}
	return (1);
}
