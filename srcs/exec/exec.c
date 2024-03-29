/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 23:14:18 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 18:46:41 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec.h"
#include "signal.h"
#include "exec/exec_cmd_checkers.h"

static t_context	*init_context(t_proc_grp *prec_grp,
t_cmd *cmd_list)
{
	t_context	*context;

	if ((context = ft_memalloc(sizeof(t_context))) == NULL)
		return (NULL);
	context->last_pipe_read = -1;
	if (prec_grp == NULL)
		context->background = is_background(cmd_list);
	else
		context->background = prec_grp->background;
	return (context);
}

t_proc_grp			*init_proc_grp(const char *name,
int background, int revived)
{
	t_proc_grp	*proc_grp;

	if ((proc_grp = new_proc_grp(background, name)) == NULL)
		return (NULL);
	proc_grp->revived = revived;
	add_proc_grp(proc_grp);
	return (proc_grp);
}

/*
**	Return -1 on error 0 otherwise
**	exec_flag func return -1 on error 0 on continue 1 on stop
*/

int					proc_grp_initialization(t_context *context, t_cmd *cmd_list,
t_proc_grp *prec_grp, const char *job_name)
{
	if (is_new_proc_grp(context))
	{
		if (create_redir_files(cmd_list) == -1)
			return (-1);
	}
	if (context->proc_grp == NULL)
	{
		if ((context->proc_grp = init_proc_grp(job_name,
	context->background, !(prec_grp == NULL))) == NULL)
			return (-1);
	}
	return (0);
}

int					exec_by_flag(t_sh_state *sh_state,
t_cmd **cmd_list, t_context *context)
{
	if (is_end_flag((const char *)(*cmd_list)->red))
		return (exec_end_flag(sh_state, cmd_list, context));
	else if (is_pipe_flag((const char *)(*cmd_list)->red))
		return (exec_pipe_flag(sh_state, cmd_list, context));
	else
		return (exec_conditioned_flag(sh_state, cmd_list, context));
}

int					exec_cmd_list(t_sh_state *sh_state,
t_cmd *cmd_list, const char *job_name, t_proc_grp *prec_grp)
{
	t_context		*context;
	int				exec_res;
	t_cmd			*acmd;

	context = init_context(prec_grp, cmd_list);
	exec_res = 0;
	acmd = cmd_list;
	while (cmd_list != NULL)
	{
		if (proc_grp_initialization(context, cmd_list,
	prec_grp, job_name) == -1 && (exec_res = -1))
			break ;
		exec_res = exec_by_flag(sh_state, &cmd_list, context);
		if (cmd_list)
			cmd_list = (cmd_list)->next;
		if (exec_res == -1 || exec_res == 1 ||
	(context->proc_grp->last_red != NULL &&
	ft_strcmp(context->proc_grp->last_red, ";") == 0))
			break ;
	}
	handle_bpid(exec_res, context);
	free_cmds(acmd);
	free(context);
	return (exec_res);
}
