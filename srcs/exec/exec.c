/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 23:14:18 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/17 18:54:20 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec.h"
#include "signal.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"

static int	cmd_is_empty(t_cmd *cmd)
{
	return (cmd == NULL || (cmd->arg == NULL &&
cmd->assign == 0 && cmd->red == NULL));
}

static int	is_background(t_cmd *cmd_list)
{
	while (!cmd_is_empty(cmd_list))
	{
		if (cmd_is_empty(cmd_list->next))
		{
			return (cmd_list->red != NULL &&
		ft_strcmp(cmd_list->red, "&") == 0);
		}
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

int		is_end_flag(t_cmd *cmd)
{
	return (cmd->red == NULL || ft_strcmp(cmd->red, "&") == 0 ||
ft_strcmp(cmd->red, ";") == 0);
}

int		is_pipe_flag(t_cmd *cmd)
{
	return (ft_strcmp(cmd->red, "|") == 0);
}

int		is_conditionned_flag(t_cmd *cmd)
{
	return (ft_strcmp(cmd->red, "&&") == 0 ||
ft_strcmp(cmd->red, "||") == 0);
}

/*
**	Return -1 on error 0 otherwise
**	exec_flag func return -1 on error 0 on continue 1 on stop
*/

int		exec_cmd_list(t_sh_state *sh_state,
t_cmd *cmd_list, const char *job_name)
{
	t_context		*context;
	int				exec_res;

	context = init_context(is_background(cmd_list));
	exec_res = 0;
	while (cmd_list != NULL)
	{
		if (context->proc_grp == NULL)
		{
			if ((context->proc_grp = init_proc_grp(job_name)) == NULL)
			{
				exec_res = -1;
				break ;
			}
		}
		if (is_end_flag(cmd_list))
			exec_res = exec_end_flag(sh_state, cmd_list, context);
		else if (is_pipe_flag(cmd_list))
			exec_res = exec_pipe_flag(sh_state, cmd_list, context);
		else if (is_conditionned_flag(cmd_list))
			exec_res = exec_conditioned_flag(sh_state, cmd_list, context);
		else
			dprintf(2, "UNHANDLED FLAG\n");
		cmd_list = (cmd_list)->next;
		if (exec_res == -1 || exec_res == 1)
			break ;
	}
	free_executed_cmds(cmd_list, context->proc_grp->remaining);
	// free context
	return (exec_res);
}
