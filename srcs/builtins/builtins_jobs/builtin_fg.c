/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_fg.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/11 21:22:24 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/12 21:05:54 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_jobs/builtin_fg.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

int			builtin_fg(t_sh_state *sh_state, int ac,
			const char **av, t_builtin_context *context)
{
	int			nres;
	t_proc_grp	*proc_grp;
	char		*err;

	add_origin(&context->origin, "fg");
	update_jobs_status();
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
	dprintf(2, "GRP = %s, PGID = %d\n", proc_grp->name, proc_grp->pgid);
	return (send_to_fg(sh_state, proc_grp));
}
