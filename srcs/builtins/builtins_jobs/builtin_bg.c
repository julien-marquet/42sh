/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_bg.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 01:20:00 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 01:25:51 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_jobs/builtin_bg.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

int			builtin_bg(t_sh_state *sh_state, int ac,
			const char **av, t_builtin_context *context)
{
	int			nres;
	t_proc_grp	*proc_grp;
	t_proc		*last_proc;
	char		*err;

	add_origin(&context->origin, "bg");
	if (ac > 1)
	{
		if ((proc_grp = find_active_proc_grp_by_name(av[1], &nres)) == NULL)
		{
			if (nres > 1)
			{
				if ((err = ft_construct_str(2, av[1], "ambiguous job")) == NULL)
					return (1);
			}
			else
			{
				if ((err = ft_construct_str(2, av[1], ": no such job")) == NULL)
					return (1);
			}
			print_error(context->origin, err, context->fds.err);
			ft_strdel(&err);
			return (1);
		}
	}
	else
	{
		proc_grp = get_first_active_proc_grp();
		if (proc_grp == NULL)
		{
			print_error(context->origin, "current: no such job", context->fds.err);
			return (1);
		}
	}
	proc_grp->background = 1;
	last_proc = get_last_proc(proc_grp);
	if (last_proc)
	{
		wake_all_processes(proc_grp);
		return (0);
	}
	return (1);
}
