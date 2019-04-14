/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 23:14:18 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 03:06:53 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec.h"
#include "signal.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"

static int	is_background(t_list	*cmd_list)
{
	t_list	*tmp;
	t_test_cmd *test;

	tmp = cmd_list;
	while (tmp != NULL && tmp->next != NULL)
	{
		test = (t_test_cmd *)tmp->content;
		tmp = tmp->next;
	}
	if (tmp != NULL)
		return (((t_test_cmd *)tmp->content)->background);
	return (0);
}

t_context	*init_context(int background)
{
	t_context	*context;

	if ((context = ft_memalloc(sizeof(t_context))) == NULL)
		return (NULL);
	context->background = background;
	context->prev_ex_flag = ex_classic;
	dprintf(2, "BACK = %d\n", context->background);
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

int		exec_cmd(t_sh_state *sh_state, t_test_cmd *test_cmd, t_context *context)
{
	int		found;

	found = 0;
	if ((found = builtins_dispatcher(sh_state, test_cmd, context)) == -1)
		return (-1);
	else if (found == 1)
		return (1);
	else
	{
		if ((found = exec_dispatcher(context)) == -1)
			return (-1);
		if (found == 1)
			return (2);
	}
	return (0);
}


int		exec_no_flag(t_sh_state *sh_state, t_test_cmd *test_cmd, t_context *context)
{
	int				process_type;

	if ((process_type = exec_cmd(sh_state, test_cmd, context)) == -1)
		return (-1);
	if (context->background == 0 && process_type != 1)
		send_to_fg(sh_state, context->proc_grp);
	context->prev_ex_flag = test_cmd->redir;
	return (0);
}
int		exec_pipe_flag(t_sh_state *sh_state, t_test_cmd *test_cmd, t_context *context)
{
	if (exec_cmd(sh_state, test_cmd, context) == -1)
		return (-1);
	context->prev_ex_flag = test_cmd->redir;
	return (0);
}
int		exec_conditioned_flag(t_sh_state *sh_state, t_test_cmd *test_cmd, t_context *context)
{
	if (exec_cmd(sh_state, test_cmd, context) == -1)
		return (-1);
	if (context->background == 0)
	{
		send_to_fg(sh_state, context->proc_grp);
	}
	context->prev_ex_flag = test_cmd->redir;
	return (0);
}

int		exec_cmd_list(t_sh_state *sh_state, t_list *cmd_list, const char *job_name)
{
	t_context		*context;
	t_test_cmd		*test_cmd;
	int				exec_res;

	context = init_context(is_background(cmd_list));
	while (cmd_list != NULL)
	{
		test_cmd = (t_test_cmd *)cmd_list->content;
		dprintf(2, "execution of %s\n", (test_cmd->str)[0]);
		if (context->proc_grp == NULL)
		{
			if ((context->proc_grp = init_proc_grp(job_name)) == NULL)
				return (1);
		}
		if (test_cmd->redir == ex_classic)
			exec_res = exec_no_flag(sh_state, test_cmd, context);
		else if (test_cmd->redir == ex_pipe)
			exec_res = exec_pipe_flag(sh_state, test_cmd, context);
		else if (test_cmd->redir == ex_and || test_cmd->redir == ex_or)
			exec_res = exec_conditioned_flag(sh_state, test_cmd, context);
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


// keep mode ;
// get background()
// 
// loop by node
// if redir = rien
// {
//		if (!pgrp)
//			new_pgrp
//		exec_dispatch()
//		if (!background)
//			send_to_fg()
// }
// if redir = && ou ||
// {
// 	if (!pgrp)
// 		new_pgrp
// 	exec_dispatch()
// 	if (!background())
// 	res = send_to_fg()
//	else
//	store remaining
// 	if (res != 0)
// 	break ;
// }
// if redir = |
// {
// 		if (!pgrp)
//			new_pgrp
//		exec_dispatch()
//		mode = |
// }

// in signal
// on update 
// continue

