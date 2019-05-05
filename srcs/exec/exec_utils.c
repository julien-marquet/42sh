/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_utils.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/20 23:16:59 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 23:09:38 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec_utils.h"

int			register_process(t_context *context, t_proc *proc, int new_pipe[3])
{
	if (context->proc_grp->pgid == 0)
		context->proc_grp->pgid = proc->pid;
	setpgid(proc->pid, context->proc_grp->pgid);
	if (context->last_pipe_read != -1)
		close(context->last_pipe_read);
	if (new_pipe[0] == 1)
	{
		context->last_pipe_read = new_pipe[READ_END];
		close(new_pipe[WRITE_END]);
	}
	else
		context->last_pipe_read = -1;
	add_proc(proc, context->proc_grp);
	return (0);
}

void		reset_signal_handlers(void)
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

int			is_absolute_path(const char *path)
{
	return (path && ft_strchr(path, '/') != NULL);
}

int			move_to_next_valid_condition(const char *condition, t_cmd **cmd)
{
	while (*cmd != NULL)
	{
		if ((*cmd)->red && ft_strcmp((*cmd)->red, condition) == 0)
			return (0);
		if (!(*cmd)->red || ft_strcmp((*cmd)->red, ";") == 0 ||
	ft_strcmp((*cmd)->red, "&") == 0)
			break ;
		*cmd = (*cmd)->next;
	}
	return (1);
}

void		handle_bpid(int exec_res, t_context *context)
{
	t_proc			*last_proc;

	if (exec_res != -1 && context->background == 1)
	{
		if ((last_proc = get_last_proc(context->proc_grp)) != NULL)
		{
			update_last_bpid(last_proc->pid);
			if (context->proc_grp->revived == 0)
				display_last_bpgid(last_proc->pid, context->proc_grp);
		}
	}
}
