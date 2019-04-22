/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_utils.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/20 23:16:59 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/22 02:44:10 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec_utils.h"

int				register_process(t_context *context, t_proc *proc, int new_pipe[3])
{
	if (context->proc_grp->pgid == 0)
		context->proc_grp->pgid = proc->pid;
	setpgid(proc->pid, context->proc_grp->pgid);
	if (context->last_pipe_read != -1)
		close(context->last_pipe_read);
	if (new_pipe[0] == 1)
		context->last_pipe_read = new_pipe[1];
	else
		context->last_pipe_read = -1;
	close(new_pipe[WRITE_END]);
	add_proc(proc, context->proc_grp);
	dprintf(2, "registered %d, %s, last = %d\n", proc->pid, proc->name, proc->last);
	return (0);
}

void			reset_signal_handlers(void)
{
	signal(SIGWINCH, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGSTOP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}