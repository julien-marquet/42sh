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

int			builtin_jobs(t_sh_state *sh_state, int ac,
const char **av, t_builtin_context *context)
{
	int		i;
	int		res;
	int		mode;
	char	*opts;

	res = 0;
	mode = 0;
	add_origin(&context->origin, "jobs");
	if (ac == 1)
		jobs_handle_display(mode, NULL, (const char *)context->origin);
	else
	{
		if ((i = handle_builtin_options(av, "pl", &opts, context)) == -1)
			res = 1;
		else if (i == 0)
		{
			print_error(context->origin,
		"usage: jobs [−l|−p] [job_id...]", 2);
			res = 1;
		}
		else
		{
			if (opts != NULL)
			{
				if (ft_strchr(opts, 'l') != NULL)
					mode = 1;
				if (ft_strchr(opts, 'p') != NULL)
					mode = 2;
			}
			if (i == ac)
				jobs_handle_display(mode, NULL, (const char *)context->origin);
			while (i < ac)
			{
				jobs_handle_display(mode, av[i], (const char *)context->origin);
				i++;
			}
			ft_strdel(&opts);
		}
	}
	return (res);
}
