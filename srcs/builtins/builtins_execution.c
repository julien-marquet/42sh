/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_execution.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 19:16:23 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 02:51:39 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_execution.h"

int				register_process(t_context *context, t_proc *proc)
{
	if (context->proc_grp->pgid == 0)
		context->proc_grp->pgid = proc->pid;
	setpgid(proc->pid, context->proc_grp->pgid);
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
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}

int				exec_builtin_as_process(t_sh_state *sh_state, t_cmd *cmd,
t_builtin_func builtin, t_context *context)
{
	pid_t	pid;
	int		res;
	t_proc	*proc;

	pid = fork();
	if (pid == 0)
	{
		reset_signal_handlers();
		setpgid(0, context->proc_grp->pgid);
		res = builtin(sh_state,
	ft_arraylen((const void **)cmd->arg), (const char **)cmd->arg, context->builtin_context);
		exit(res);
	}
	else
	{
		if ((proc = new_proc(pid, cmd->arg[0], context->last, cmd->next)) == NULL)
			return (1);
		if (register_process(context, proc) == 1)
			return (1);
	}
	return (0);
}

int				exec_builtin_as_function(t_sh_state *sh_state, const char **av,
t_builtin_func builtin, t_context *context)
{
	return (builtin(sh_state, ft_arraylen((const void **)av),
av, context->builtin_context));
}
