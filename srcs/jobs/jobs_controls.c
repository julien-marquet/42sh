/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_controls.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:42:35 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 02:15:10 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_controls.h"

int			send_to_fg(t_sh_state *sh_state, t_proc_grp *proc_grp)
{
	int		stat_loc;
	t_proc	*last_proc;

	stat_loc = 0;
	last_proc = get_last_proc(proc_grp);
	set_term_state_backup(sh_state);
	tcsetpgrp(0, proc_grp->pgid);
	waitpid(last_proc->pid, &stat_loc, WUNTRACED);
	tcsetpgrp(0, sh_state->shell_pid);
	set_term_state(sh_state);
	return (0);
}