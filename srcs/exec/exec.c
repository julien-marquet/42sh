/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 23:14:18 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 23:06:37 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec.h"
#include "signal.h"
#include "exec/exec_cmd_checkers.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"

static t_context	*init_context(t_proc_grp *prec_grp,
t_cmd *cmd_list)
{
	t_context	*context;

	if ((context = ft_memalloc(sizeof(t_context))) == NULL)
		return (NULL);
	if (prec_grp == NULL)
		context->background = is_background(cmd_list);
	else
	{
		context->background = prec_grp->background;
		prec_grp->revived = 1;
	}
	return (context);
}

t_proc_grp	*init_proc_grp(const char *name, int background)
{
	t_proc_grp	*proc_grp;

	if ((proc_grp = new_proc_grp(background, name)) == NULL)
		return (NULL);
	add_proc_grp(proc_grp);
	return (proc_grp);
}

/*
**	Return -1 on error 0 otherwise
**	exec_flag func return -1 on error 0 on continue 1 on stop
*/

int		exec_cmd_list(t_sh_state *sh_state,
t_cmd *cmd_list, const char *job_name, t_proc_grp *prec_grp)
{
	t_context		*context;
	int				exec_res;

	context = init_context(prec_grp, cmd_list);
	exec_res = 0;
	while (cmd_list != NULL)
	{
		if (context->proc_grp == NULL)
		{
			if ((context->proc_grp = init_proc_grp(job_name,
		context->background)) == NULL)
			{
				exec_res = -1;
				break ;
			}
		}
		if (is_end_flag((const char *)cmd_list->red))
			exec_res = exec_end_flag(sh_state, cmd_list, context);
		else if (is_pipe_flag((const char *)cmd_list->red))
			exec_res = exec_pipe_flag(sh_state, cmd_list, context);
		else if (is_conditionned_flag((const char *)cmd_list->red))
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
