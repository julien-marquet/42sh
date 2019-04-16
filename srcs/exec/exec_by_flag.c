/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_by_flag.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 02:56:08 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 03:01:53 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec_by_flag.h"

static int	exec_cmd(t_sh_state *sh_state, t_cmd *cmd, t_context *context)
{
	int		found;

	found = 0;
	if ((found = builtins_dispatcher(sh_state, cmd, context)) == -1)
		return (-1);
	else if (found > 0)
		return (found);
	else
	{
		if ((found = exec_dispatcher(context)) == -1)
			return (-1);
		if (found == 1)
			return (2);
	}
	return (0);
}

/*
**	WARNING Do not try to free context->prev_ex_flag or
**	try to access it after cmd_list has been freed
*/

int			exec_no_flag(t_sh_state *sh_state, t_cmd *cmd, t_context *context)
{
	int				process_type;

	context->last = 1;
	if ((process_type = exec_cmd(sh_state, cmd, context)) == -1)
		return (-1);
	if (context->background == 0 && process_type != 1)
		send_to_fg(sh_state, context->proc_grp);
	context->prev_ex_flag = cmd->red;
	return (0);
}

int			exec_pipe_flag(t_sh_state *sh_state, t_cmd *cmd, t_context *context)
{
	context->last = 0;
	if (exec_cmd(sh_state, cmd, context) == -1)
		return (-1);
	context->prev_ex_flag = cmd->red;
	return (0);
}

static int	handle_processes_return(t_sh_state *sh_state, t_context *context,
t_cmd *cmd)
{
	t_proc	*last_proc;

	send_to_fg(sh_state, context->proc_grp);
	last_proc = get_last_proc(context->proc_grp);
	if (last_proc->status == exited && last_proc->code == 0)
	{
		if (ft_strcmp(cmd->red, "||") == 0)
			return (1);
	}
	else if (last_proc->status == signaled || last_proc->status == exited)
	{
		if (ft_strcmp(cmd->red, "&&") == 0)
			return (1);
	}
	return (0);
}

int			exec_conditioned_flag(t_sh_state *sh_state, t_cmd *cmd,
t_context *context)
{
	int		process_type;

	context->last = 1;
	if ((process_type = exec_cmd(sh_state, cmd, context)) == -1)
		return (-1);
	if (context->background == 0)
	{
		if (process_type == 2)
		{
			if (handle_processes_return(sh_state, context, cmd) == 1)
				return (1);
		}
		else
		{
			if (sh_state->status == 0 && ft_strcmp(cmd->red, "||") == 0)
				return (1);
			else if (sh_state->status != 0 && ft_strcmp(cmd->red, "&&") == 0)
				return (1);
		}
	}
	context->prev_ex_flag = cmd->red;
	return (0);
}
