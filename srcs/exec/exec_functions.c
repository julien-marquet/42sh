/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_functions.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 22:50:48 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 23:09:06 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec_functions.h"

static int		exec_parallel(t_sh_state *sh_state, const char **parsed,
t_context *context)
{
	int		found;
	t_proc	*proc;

	if ((found = builtins_dispatcher(sh_state, parsed, context)) == -1)
		return (1);
	else if (found == 0)
		found = exec_dispatcher(context);
	if (found == 1)
		dprintf(2, "EXEC_DONE\n");

	if (context->proc_grp != NULL && context->background == 0)
	{
		if ((proc = get_last_proc(context->proc_grp)) == NULL)
			return (1);
		update_jobs_status(proc->pid);
	}
	return (0);
}

static int		exec_solo(t_sh_state *sh_state, const char **parsed,
t_context *context)
{
	int		found;
	t_proc	*proc;

	if ((found = builtins_dispatcher(sh_state, parsed, context)) == -1)
		return (1);
	else if (found == 1)
	{
		found = exec_dispatcher(context);
		if (context->proc_grp != NULL && context->background == 0)
		{
			if ((proc = get_last_proc(context->proc_grp)) == NULL)
				return (1);
			update_jobs_status(proc->pid);
		}
	}
	if (found == 1)
		dprintf(2, "EXEC_DONE\n");
	return (0);
}

t_exec_func		get_exec_function(t_exec_mode exec_mode)
{
	t_exec_func		func;

	func = NULL;
	if (exec_mode == parallel)
		func = exec_parallel;
	else if (exec_mode == solo)
		func = exec_solo;
	return (func);
}
