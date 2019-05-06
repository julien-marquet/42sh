/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_null.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 19:50:57 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 19:55:42 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec_null.h"

static void	handle_null_pipes(t_context *context, t_cmd *cmd)
{
	int		new_pipe[2];

	if (context->last_pipe_read != -1)
		close(context->last_pipe_read);
	if (cmd->red && ft_strcmp(cmd->red, "|") == 0)
	{
		if (pipe(new_pipe) == -1)
		{
			context->last_pipe_read = -1;
			return ;
		}
		context->last_pipe_read = new_pipe[0];
		close(new_pipe[1]);
	}
	else
		context->last_pipe_read = -1;
}

static int	handle_null_last_proc(t_sh_state *sh_state, t_cmd **cmd,
t_context *context)
{
	t_proc	*last_proc;

	if ((last_proc = get_last_proc_all(context->proc_grp)) == NULL)
		return (-1);
	if (context->proc_grp->background == 0)
	{
		sh_state->status = last_proc->code;
		if ((last_proc->code != 0 && (*cmd)->red &&
	ft_strcmp((*cmd)->red, "&&") == 0))
			return (move_to_next_valid_condition("||", cmd));
		else if (last_proc->code == 0 && (*cmd)->red &&
	ft_strcmp((*cmd)->red, "||") == 0)
			return (move_to_next_valid_condition("&&", cmd));
	}
	else
	{
		(*cmd)->next = NULL;
		check_revive_process_group(sh_state, context->proc_grp, last_proc);
	}
	return (0);
}

int			handle_null_cmd(t_sh_state *sh_state, t_cmd **cmd,
t_context *context, int err)
{
	char	*cmd_str;
	int		is_null;

	cmd_str = (*cmd) && (*cmd)->arg ? (*cmd)->arg[0] : NULL;
	is_null = cmd_is_null((*cmd));
	if (add_null_proc(context->proc_grp, (*cmd)->str, (*cmd), err))
		return (-1);
	if (!is_last((*cmd)))
	{
		handle_null_pipes(context, *cmd);
		return (0);
	}
	else
		return (handle_null_last_proc(sh_state, cmd, context));
}
