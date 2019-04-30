/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_by_flag.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 02:56:08 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 10:25:10 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec_by_flag.h"

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

static int	handle_null_cmd(t_sh_state *sh_state, t_cmd **cmd,
t_proc_grp *proc_grp, int err)
{
	char	*cmd_str;
	int		is_null;

	cmd_str = (*cmd) && (*cmd)->arg ? (*cmd)->arg[0] : NULL;
	is_null = cmd_is_null((*cmd));
	if (add_null_proc(proc_grp, (*cmd)->str, (*cmd)))
		return (-1);
	if (is_last((*cmd)) && proc_grp->background == 0)
	{
		sh_state->status = 126;
		if (err == 0)
			sh_state->status = is_null && (*cmd)->assign == 1 ? 0 : 127;
		if (count_true_procs(proc_grp) == 0)
		{
			if ((!is_null && (*cmd)->red &&
		ft_strcmp((*cmd)->red, "&&") == 0))
				return (move_to_next_valid_condition("||", cmd));
			else if (is_null && (*cmd)->assign && (*cmd)->red &&
		ft_strcmp((*cmd)->red, "||") == 0)
				return (move_to_next_valid_condition("&&", cmd));
			return (0);
		}
		send_to_fg(sh_state, proc_grp);
		return (1);
	}
	return (0);
}

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
		return (handle_null_cmd(sh_state, cmd, context->proc_grp,
	process_type));
	}
	else
	{
		if (context->background == 0 && process_type != 1)
			send_to_fg(sh_state, context->proc_grp);
	}
	return (1);
}

int			exec_pipe_flag(t_sh_state *sh_state, t_cmd **cmd, t_context *context)
{
	int		process_type;

	context->last = 0;
	process_type = exec_cmd(sh_state, (*cmd), context);
	context->proc_grp->remaining = (*cmd)->next;
	ft_strdel(&context->proc_grp->last_red);
	context->proc_grp->last_red = ft_strdup((*cmd)->red);
	if (process_type <= 0)
	{
		return (handle_null_cmd(sh_state, cmd, context->proc_grp,
	process_type));
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
		return (handle_null_cmd(sh_state, cmd, context->proc_grp,
	process_type));
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
			if (sh_state->status == 0 && ft_strcmp((*cmd)->red, "||") == 0)
				return (move_to_next_valid_condition("&&", cmd));
			else if (sh_state->status != 0 && ft_strcmp((*cmd)->red, "&&") == 0)
				return (move_to_next_valid_condition("||", cmd));
		}
	}
	else
		return (1);
	return (0);
}
