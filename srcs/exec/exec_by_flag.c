/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_by_flag.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 02:56:08 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 23:01:49 by jmarquet    ###    #+. /#+    ###.fr     */
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

int			exec_end_flag(t_sh_state *sh_state, t_cmd *cmd, t_context *context)
{
	int				process_type;
	int				arg_len;

	dprintf(2, "EXEC END %s\n", cmd->str);
	context->last = 1;
	arg_len = ft_arraylen((const void **)cmd->arg);
	if (arg_len > 0)
	{
		if ((process_type = exec_cmd(sh_state, cmd, context)) == -1)
			return (-1);
		context->proc_grp->remaining = cmd->next;
	}
	context->proc_grp->last_red = ft_strdup(cmd->red);
	if (arg_len > 0 && context->background == 0 && process_type != 1)
		send_to_fg(sh_state, context->proc_grp);
	if (cmd->red != NULL && ft_strcmp(cmd->red, ";") == 0)
		return (1);
	return (1);
}

int			exec_pipe_flag(t_sh_state *sh_state, t_cmd *cmd, t_context *context)
{
	dprintf(2, "EXEC PIPE %s\n", cmd->str);
	context->last = 0;
	if (exec_cmd(sh_state, cmd, context) == -1)
		return (-1);
	context->proc_grp->remaining = cmd->next;
	context->proc_grp->last_red = ft_strdup(cmd->red);
	return (0);
}

int			exec_conditioned_flag(t_sh_state *sh_state, t_cmd *cmd,
t_context *context)
{
	int		process_type;

	context->last = 1;
	if ((process_type = exec_cmd(sh_state, cmd, context)) == -1)
		return (-1);
	context->proc_grp->last_red = ft_strdup(cmd->red);
	context->proc_grp->remaining = cmd->next;
	if (context->background == 0)
	{
		if (process_type == 2)
		{
			if (send_to_fg(sh_state, context->proc_grp) == 1)
				return (-1);
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
	else
		return (1);
	return (0);
}
