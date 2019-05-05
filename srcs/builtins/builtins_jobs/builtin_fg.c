/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_fg.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/11 21:22:24 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 12:33:54 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_jobs/builtin_fg.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

static int	check_arg(const char *arg, t_proc_grp **proc_grp, char *origin)
{
	int			nres;
	char		*err;

	nres = 0;
	if (str_is_digit(arg) == 1)
		*proc_grp = find_active_proc_grp_by_num(ft_atoi(arg));
	if (*proc_grp == NULL)
	{
		if ((*proc_grp = find_active_proc_grp_by_needle(arg,
	&nres)) != NULL)
			ft_putendl((*proc_grp)->name);
	}
	if (*proc_grp == NULL)
	{
		if (nres > 1)
			err = ft_construct_str(2, arg, ": ambiguous job");
		else
			err = ft_construct_str(2, arg, ": no such job");
		print_error(origin, err, 2);
		ft_strdel(&err);
		return (1);
	}
	return (0);
}

int			builtin_fg(t_sh_state *sh_state, int ac,
			const char **av, t_builtin_context *context)
{
	t_proc_grp	*proc_grp;

	add_origin(&context->origin, "fg");
	proc_grp = NULL;
	if (context->is_process)
	{
		print_error(context->origin, "no job control", 2);
		return (1);
	}
	else if (ac > 1)
	{
		if (check_arg(av[1], &proc_grp, context->origin) == 1)
			return (1);
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
