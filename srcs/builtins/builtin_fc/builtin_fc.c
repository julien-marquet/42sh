/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_fc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 22:10:25 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 23:32:21 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_fc.h"

int				fc_exit(t_fc_infos *fc_infos, int ret)
{
	ft_strdel(&fc_infos->opts);
	ft_strdel(&fc_infos->editor);
	free(fc_infos);
	return (ret);
}

static void		fc_range(t_sh_state *sh_state, const char **av,
t_fc_infos *fc_infos)
{
	if (av[0])
	{
		fc_infos->first = get_history_index_rev(sh_state->history,
		fc_get_hist_num(sh_state, av[0]));
		fc_infos->is_set++;
		if (av[1])
		{
			if (fc_get_hist_num(sh_state, av[0]) >
			fc_get_hist_num(sh_state, av[1]))
			{
				add_valid(fc_infos, 'r');
				fc_infos->last = fc_infos->first;
				fc_infos->first = get_history_index_rev(sh_state->history,
				fc_get_hist_num(sh_state, av[1]));
			}
			else
				fc_infos->last = get_history_index_rev(sh_state->history,
				fc_get_hist_num(sh_state, av[1]));
			fc_infos->is_set++;
		}
	}
}

static int		check_editor(t_fc_infos *fc_infos)
{
	char	**nul;
	int		valid;
	int		i;

	valid = 1;
	i = 0;
	if (fc_infos->editor)
	{
		if (!(nul = ft_strsplit(fc_infos->editor, ' ')))
			return (0);
		while (nul[i])
		{
			if (ft_strstr(nul[i], "fc") && ft_strlen(nul[i]) == 2)
				valid = 0;
			i++;
		}
		i = 0;
		while (nul[i])
			ft_strdel(&nul[i++]);
		free(nul);
	}
	return (valid);
}

static int		fc_dispatch(t_sh_state *sh_state, const char **av,
t_fc_infos *fc_infos, t_builtin_context *context)
{
	int		valid_editor;
	int		ret;

	valid_editor = check_editor(fc_infos);
	ret = 0;
	fc_range(sh_state, av, fc_infos);
	if (!sh_state->history || !sh_state->history->next || valid_editor == 0)
	{
		print_error(context->origin, "history specification out of range", 2);
		return (fc_exit(fc_infos, 0));
	}
	if (fc_infos->replace)
		ret = fc_replace_exec(sh_state, fc_infos);
	else if (fc_infos->opts != NULL && ft_strchr(fc_infos->opts, 'l') != NULL)
		ret = fc_print(sh_state->history, fc_infos, 1);
	else
		ret = fc_exec(sh_state, fc_infos);
	return (fc_exit(fc_infos, ret));
}

int				builtin_fc(t_sh_state *sh_state, int ac, const char **av,
t_builtin_context *context)
{
	t_fc_infos	*fc_infos;
	int			args_i;

	(void)ac;
	add_origin(&context->origin, "fc");
	if (context->is_process)
	{
		print_error(context->origin, "no job control", 2);
		return (1);
	}
	if (!(fc_infos = ft_memalloc(sizeof(t_fc_infos))))
		return (1);
	if (!(fc_infos->opts = ft_strnew(5)))
		return (fc_exit(fc_infos, 1));
	if ((args_i = fc_options(av, fc_infos, context)) == -1)
		return (fc_exit(fc_infos, 1));
	else if (args_i == 0)
	{
		print_error(context->origin, FC_USAGE, 2);
		return (fc_exit(fc_infos, 1));
	}
	return (fc_dispatch(sh_state, av + args_i, fc_infos, context));
}
