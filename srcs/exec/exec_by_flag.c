/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_by_flag.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 02:56:08 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 03:25:15 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec_by_flag.h"

static int	handle_null_cmd(t_sh_state *sh_state, const char *cmd_str, t_cmd *cmd_list, t_proc_grp *proc_grp)
{
	int		is_null;

	if ((is_null = cmd_is_null(cmd_list)) == 0)
	{
		ft_putstr_fd("42sh: ", 2);
		if (cmd_str)
			ft_putstr_fd(cmd_str, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	if (add_null_proc(proc_grp, cmd_list->str, cmd_list))
		return (-1);
	if (is_last(cmd_list) && proc_grp->background == 0)
	{
		if (is_null)
			sh_state->status = 127;
		if (count_true_procs(proc_grp) == 0)
		{
			if (!is_null && cmd_list->red &&
		ft_strcmp(cmd_list->red, "&&") == 0)
				return (1);
			else if (is_null && cmd_list->assign &&
		cmd_list->red && ft_strcmp(cmd_list->red, "||") == 0)
				return (1);
			return (0);
		}
		send_to_fg(sh_state, proc_grp);
		return (1);
	}
	return (0);
}

static int	exec_cmd(t_sh_state *sh_state, t_cmd *cmd, t_context *context)
{
	int		found;

	found = 0;
	if (cmd_is_null(cmd))
		return (0);
	else
	{
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
	}
	return (0);
}

int			exec_end_flag(t_sh_state *sh_state, t_cmd *cmd, t_context *context)
{
	int				process_type;

	context->last = 1;
	if ((process_type = exec_cmd(sh_state, cmd, context)) == -1)
		return (-1);
	context->proc_grp->remaining = cmd->next;
	ft_strdel(&context->proc_grp->last_red);
	context->proc_grp->last_red = ft_strdup(cmd->red);
	if (process_type == 0)
		return (handle_null_cmd(sh_state,
	cmd && cmd->arg ? cmd->arg[0] : NULL, cmd, context->proc_grp));
	else
	{
		if (context->background == 0 && process_type != 1)
			send_to_fg(sh_state, context->proc_grp);
	}
	return (1);
}

int			exec_pipe_flag(t_sh_state *sh_state, t_cmd *cmd, t_context *context)
{
	int		process_type;

	context->last = 0;
	if ((process_type = exec_cmd(sh_state, cmd, context)) == -1)
		return (-1);
	context->proc_grp->remaining = cmd->next;
	ft_strdel(&context->proc_grp->last_red);
	context->proc_grp->last_red = ft_strdup(cmd->red);
	if (process_type == 0)
	{
		return (handle_null_cmd(sh_state,
	cmd && cmd->arg ? cmd->arg[0] : NULL, cmd, context->proc_grp));
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
	ft_strdel(&context->proc_grp->last_red);
	context->proc_grp->last_red = ft_strdup(cmd->red);
	context->proc_grp->remaining = cmd->next;
	if (process_type == 0)
	{
		return (handle_null_cmd(sh_state,
	cmd && cmd->arg ? cmd->arg[0] : NULL, cmd, context->proc_grp));
	}
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
