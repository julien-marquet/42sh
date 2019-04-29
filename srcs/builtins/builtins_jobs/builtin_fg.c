/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_fg.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/11 21:22:24 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 10:40:48 by jmarquet    ###    #+. /#+    ###.fr     */
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
	proc_grp = NULL;
	nres = 0;
	if (context->is_process)
	{
		print_error(context->origin, "no job control", 2);
		return (1);
	}
	else if (ac > 1)
	{
		if (str_is_digit(av[1]) == 1)
			proc_grp = find_active_proc_grp_by_num(ft_atoi(av[1]));
		if (proc_grp == NULL)
			proc_grp = find_active_proc_grp_by_name(av[1], &nres);
		if (proc_grp == NULL)
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
			print_error(context->origin, err, 2);
			ft_strdel(&err);
			return (1);
		}
	}
	else
	{
		proc_grp = get_first_active_proc_grp();
		if (proc_grp == NULL)
		{
			print_error(context->origin, "current: no such job", 2);
			return (1);
		}
	}
	proc_grp->background = 0;
	return (send_to_fg(sh_state, proc_grp));
}
