/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 23:14:18 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 02:50:06 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec.h"
#include "signal.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"

static int	is_background(t_cmd *cmd_list)
{
	while (cmd_list != NULL)
	{
		if (cmd_list->next == NULL && cmd_list->red != NULL)
			return (ft_strcmp(cmd_list->red, "&") == 0);
		cmd_list = cmd_list->next;
	}
	return (0);
}

t_context	*init_context(int background)
{
	t_context	*context;

	if ((context = ft_memalloc(sizeof(t_context))) == NULL)
		return (NULL);
	context->background = background;
	return (context);
}

t_proc_grp	*init_proc_grp(const char *name)
{
	t_proc_grp	*proc_grp;

	if ((proc_grp = new_proc_grp(0, name)) == NULL)
		return (NULL);
	add_proc_grp(proc_grp);
	return (proc_grp);
}

int		exec_cmd(t_sh_state *sh_state, t_cmd *cmd, t_context *context)
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

int		exec_no_flag(t_sh_state *sh_state, t_cmd *cmd, t_context *context)
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
int		exec_pipe_flag(t_sh_state *sh_state, t_cmd *cmd, t_context *context)
{
	context->last = 0;
	if (exec_cmd(sh_state, cmd, context) == -1)
		return (-1);
	context->prev_ex_flag = cmd->red;
	return (0);
}
int		exec_conditioned_flag(t_sh_state *sh_state, t_cmd *cmd, t_context *context)
{
	t_proc	*last_proc;
	int		process_type;

	context->last = 1;
	if ((process_type = exec_cmd(sh_state, cmd, context)) == -1)
		return (-1);
	if (context->background == 0)
	{
		if (process_type == 2)
		{
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

int		exec_cmd_list(t_sh_state *sh_state, t_cmd *cmd_list, const char *job_name)
{
	t_context		*context;
	int				exec_res;

	context = init_context(is_background(cmd_list));
	while (cmd_list != NULL)
	{
		dprintf(2, "execution of %s\n", (cmd_list->str));
		if (context->proc_grp == NULL)
		{
			if ((context->proc_grp = init_proc_grp(job_name)) == NULL)
				return (1);
		}
		if (cmd_list->red == NULL || ft_strcmp(cmd_list->red, "&") == 0)
			exec_res = exec_no_flag(sh_state, cmd_list, context);
		else if (ft_strcmp(cmd_list->red, "|") == 0)
			exec_res = exec_pipe_flag(sh_state, cmd_list, context);
		else if (ft_strcmp(cmd_list->red, "&&") == 0 ||
	ft_strcmp(cmd_list->red, "||") == 0)
			exec_res = exec_conditioned_flag(sh_state, cmd_list, context);
		if (exec_res == -1)
			return (1);
		if (exec_res == 1)
		{
			// handle stopped
			return (0);
		}
		cmd_list = cmd_list->next;
	}
	return (0);
}
