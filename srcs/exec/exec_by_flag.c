/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_by_flag.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 02:56:08 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 03:00:30 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec_by_flag.h"

static void	handle_not_found_error(const char *cmd_str, t_cmd *cmd_list, t_proc_grp *proc_grp)
{
	t_proc	*last_proc;

	if (cmd_is_empty(cmd_list->next))
	{
		if ((last_proc = get_last_proc(proc_grp)) != NULL)
			last_proc->last = 1;
	}
	ft_putstr_fd("42sh: ", 2);
	if (cmd_str)
		ft_putstr_fd(cmd_str, 2);
	ft_putstr_fd(": command not found\n", 2);
}

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

int			exec_end_flag(t_sh_state *sh_state, t_cmd *cmd, t_context *context)
{
	int				process_type;

	context->last = 1;
	if ((process_type = exec_cmd(sh_state, cmd, context)) == -1)
		return (-1);
	context->proc_grp->remaining = cmd->next;
	context->proc_grp->last_red = ft_strdup(cmd->red);
	if (process_type == 0)
		handle_not_found_error(cmd ? cmd->arg[0] : NULL, cmd, context->proc_grp);
	else
	{
		if (context->background == 0 && process_type != 1)
			send_to_fg(sh_state, context->proc_grp);
		if (cmd->red != NULL && (ft_strcmp(cmd->red, ";") == 0 ||
	ft_strcmp(cmd->red, "&") == 0))
			return (1);
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
	context->proc_grp->last_red = ft_strdup(cmd->red);
	if (process_type == 0)
		handle_not_found_error(cmd ? cmd->arg[0] : NULL, cmd, context->proc_grp);
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
	if (process_type == 0)
		handle_not_found_error(cmd ? cmd->arg[0] : NULL, cmd, context->proc_grp);
	else if (context->background == 0)
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
