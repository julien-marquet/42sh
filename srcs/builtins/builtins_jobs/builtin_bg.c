/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_bg.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 01:20:00 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 12:34:12 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_jobs/builtin_bg.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

static int	check_arg(const char *arg, t_proc_grp **proc_grp, char *origin)
{
	char		*err;
	int			nres;

	*proc_grp = NULL;
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

int			error(char *origin, char *msg)
{
	print_error(origin, msg, 2);
	return (1);
}

int			builtin_bg(t_sh_state *sh_state, int ac,
			const char **av, t_builtin_context *context)
{
	t_proc_grp	*proc_grp;
	t_proc		*last_proc;

	add_origin(&context->origin, "bg");
	if (context->is_process)
		return (error(context->origin, "no job control"));
	else if (ac > 1)
	{
		if (check_arg(av[1], &proc_grp, context->origin) == 1)
			return (1);
	}
	else
	{
		proc_grp = get_first_active_proc_grp();
		if (proc_grp == NULL)
			return (error(context->origin, "current: no such job"));
	}
	proc_grp->background = 1;
	if ((last_proc = get_last_proc(proc_grp)) != NULL)
	{
		update_last_bpid(last_proc->pid);
		wake_all_processes(proc_grp);
		return (0);
	}
	return (1);
}
