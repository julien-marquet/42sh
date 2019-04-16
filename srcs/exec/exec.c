/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 23:14:18 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 19:29:51 by jmarquet    ###    #+. /#+    ###.fr     */
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

/*
**	Return -1 on error 0 on exited 1 on stopped
*/

int		exec_cmd_list(t_sh_state *sh_state, t_cmd *cmd_list, const char *job_name)
{
	t_context		*context;
	int				exec_res;

	context = init_context(is_background(cmd_list));
	exec_res = 0;
	while (cmd_list != NULL)
	{
		dprintf(2, "execution of %s\n", (cmd_list->str));
		if (context->proc_grp == NULL)
		{
			if ((context->proc_grp = init_proc_grp(job_name)) == NULL)
			{
				exec_res = -1;
				break ;
			}
		}
		if (cmd_list->red == NULL || ft_strcmp(cmd_list->red, "&") == 0)
			exec_res = exec_no_flag(sh_state, cmd_list, context);
		else if (ft_strcmp(cmd_list->red, "|") == 0)
			exec_res = exec_pipe_flag(sh_state, cmd_list, context);
		else if (ft_strcmp(cmd_list->red, "&&") == 0 ||
	ft_strcmp(cmd_list->red, "||") == 0)
			exec_res = exec_conditioned_flag(sh_state, cmd_list, context);
		if (exec_res != 0)
			break ;
		cmd_list = cmd_list->next;
	}
	free_executed_cmds(cmd_list, context->proc_grp->remaining);
	return (exec_res);
}
