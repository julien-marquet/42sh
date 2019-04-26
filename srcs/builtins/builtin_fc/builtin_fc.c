/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_fc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 22:10:25 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 22:00:24 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_fc.h"

int				fc_exec(t_sh_state *sh_state, t_fc_infos *fc_infos, t_builtin_context *context)
{
	(void)sh_state;
	(void)fc_infos;
	(void)context;
	return (0);
}

static int		fc_dispatch(t_sh_state *sh_state, const char **av, t_fc_infos *fc_infos, t_builtin_context *context)
{
	int i;

	i = 0;
	if (av[0])
	{
		fc_infos->first = fc_get_hist_num(sh_state, av[0]);
		if (av[1])
			fc_infos->last = fc_get_hist_num(sh_state, av[1]);
	}
	if (fc_infos->first == 0 || fc_infos->first == 0 || !sh_state->history->next)
	{
		free(fc_infos);
		print_error(context->origin, "history specification out of range", context->fds.err);
		return (1);
	}
	if (fc_infos->opts != NULL && ft_strchr(fc_infos->opts, 'l') != NULL)
		return (fc_print(sh_state->history, fc_infos));
	else
		return (fc_exec(sh_state, fc_infos, context));
	return (0);
}

int				builtin_fc(t_sh_state *sh_state, int ac, const char **av, t_builtin_context *context)
{
	t_fc_infos	*fc_infos;
	int			args_i;

	(void)ac;
	add_origin(&context->origin, "fc");
	fc_infos = ft_memalloc(sizeof(t_fc_infos));
	if (!(fc_infos->opts = ft_strnew(5)))
		return (-1);
	fc_infos->first = -1;
	fc_infos->last = -1;
	if ((args_i = fc_options(av, fc_infos, context)) == -1)
		return (1);
	else if (args_i == 0)
	{
		print_error(context->origin, "usage: fc [-e ename] [-nlr] [first] [last] or fc -s [pat=rep] [cmd]", context->fds.err);
		return (1);
	}
	else
		return (fc_dispatch(sh_state, av + args_i, fc_infos, context));
}
