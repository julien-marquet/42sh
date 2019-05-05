/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_jobs.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/11 20:45:56 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 20:29:27 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_jobs/builtin_jobs.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

static void	update_mode(char *opts, int *mode)
{
	if (opts != NULL)
	{
		if (ft_strchr(opts, 'l') != NULL)
			*mode = 1;
		if (ft_strchr(opts, 'p') != NULL)
			*mode = 2;
	}
	ft_strdel(&opts);
}

static void	init(int *res, int *mode, int ac, char **origin)
{
	*res = 0;
	*mode = 0;
	add_origin(origin, "jobs");
	if (ac == 1)
		jobs_handle_display(*mode, NULL, *origin);
}

static void	error(char *origin, int *res)
{
	print_error(origin, "usage: jobs [-l|-p] [job_id...]", 2);
	*res = 1;
}

int			builtin_jobs(t_sh_state *sh_state, int ac,
const char **av, t_builtin_context *context)
{
	int		i;
	int		res;
	int		mode;
	char	*opts;

	init(&res, &mode, ac, &context->origin);
	if (ac != 1)
	{
		if ((i = handle_builtin_options(av, "pl", &opts, context)) == -1)
			res = 1;
		else if (i == 0)
			error(context->origin, &res);
		else
		{
			update_mode(opts, &mode);
			if (i == ac)
				jobs_handle_display(mode, NULL, (const char *)context->origin);
			while (i < ac)
			{
				jobs_handle_display(mode, av[i], (const char *)context->origin);
				i++;
			}
		}
	}
	return (res);
}
