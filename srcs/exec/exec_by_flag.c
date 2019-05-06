/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_by_flag.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 02:56:08 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 20:00:26 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec_by_flag.h"

static int	exec_cmd(t_sh_state *sh_state, t_cmd *cmd,
t_context *context)
{
	int		found;

	found = 0;
	if (cmd_is_null(cmd))
		return (0);
	else
	{
		if ((found = builtins_dispatcher(sh_state, cmd, context)) < 0)
			return (found);
		else if (found == 0)
		{
			if ((found = exec_dispatcher(sh_state, cmd, context)) <= 0)
				return (found);
			if (found == 1)
				return (2);
		}
	}
	return (found);
}

int			exec_end_flag(t_sh_state *sh_state, t_cmd **cmd, t_context *context)
{
	int				process_type;

	context->last = 1;
	process_type = exec_cmd(sh_state, (*cmd), context);
	context->proc_grp->remaining = (*cmd)->next;
	ft_strdel(&context->proc_grp->last_red);
	context->proc_grp->last_red = ft_strdup((*cmd)->red);
	if (process_type <= 0)
	{
		return (handle_null_cmd(sh_state, cmd, context,
	process_type));
	}
	else
	{
		if (context->background == 0 && process_type != 1)
			send_to_fg(sh_state, context->proc_grp);
	}
	return (1);
}

int			exec_pipe_flag(t_sh_state *sh_state, t_cmd **cmd,
t_context *context)
{
	int		process_type;

	context->last = 0;
	process_type = exec_cmd(sh_state, (*cmd), context);
	context->proc_grp->remaining = (*cmd)->next;
	ft_strdel(&context->proc_grp->last_red);
	context->proc_grp->last_red = ft_strdup((*cmd)->red);
	if (process_type <= 0)
	{
		return (handle_null_cmd(sh_state, cmd, context,
	process_type));
	}
	return (0);
}

static int	handle_foreground_conditionned(int process_type,
t_sh_state *sh_state, t_context *context, t_cmd **cmd)
{
	if (process_type == 2)
	{
		if (send_to_fg(sh_state, context->proc_grp) == 1)
			return (-1);
		return (1);
	}
	else
	{
		if (sh_state->status == 0 && ft_strcmp((*cmd)->red, "||") == 0)
			return (move_to_next_valid_condition("&&", cmd));
		else if (sh_state->status != 0 && ft_strcmp((*cmd)->red, "&&") == 0)
			return (move_to_next_valid_condition("||", cmd));
	}
	return (0);
}

int			exec_conditioned_flag(t_sh_state *sh_state, t_cmd **cmd,
t_context *context)
{
	int		process_type;

	context->last = 1;
	process_type = exec_cmd(sh_state, *cmd, context);
	ft_strdel(&context->proc_grp->last_red);
	context->proc_grp->last_red = ft_strdup((*cmd)->red);
	context->proc_grp->remaining = (*cmd)->next;
	if (process_type <= 0)
	{
		return (handle_null_cmd(sh_state, cmd, context,
	process_type));
	}
	else if (process_type == 2)
		(*cmd)->next = NULL;
	if (context->background == 0)
	{
		return (handle_foreground_conditionned(process_type, sh_state,
	context, cmd));
	}
	else
		return (1);
}
