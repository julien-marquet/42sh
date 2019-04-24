/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_fc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 22:10:25 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/24 20:55:52 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_fc.h"

static int		is_builtin_option(const char *str)
{
	size_t	i;
	size_t	digit;

	i = 0;
	digit = 0;
	while (str[i])
		digit += ft_isdigit(str[i++]);
	return (str && str[0] == '-' && str[1] != '\0' && digit == 0);
}

static void		add_valid(t_fc_infos *fc_infos, char new)
{
	size_t len;
	
	len = ft_strlen(fc_infos->opts);		
	if (!ft_strchr(fc_infos->opts, new))
		fc_infos->opts[len] = new;
}

static int		fc_option_e(const char **av, t_fc_infos *fc_infos, int i, t_builtin_context *context)
{
	if (av[++i] != NULL)
	{
		if (fc_infos->editor != NULL)
			ft_strdel(&fc_infos->editor);
		if (!(fc_infos->editor = ft_strdup(av[i])))
			return (-1);
	}
	else
	{
		print_error(context->origin, "-e: option requires an argument", context->fds.err);
		return (0);
	}
	return (i);
}

static int		fc_options(const char **av, t_fc_infos *fc_infos, t_builtin_context *context)
{
	int i;
	int j;

	i = 1;
	while (av[i] && is_builtin_option(av[i]))
	{
		if (ft_strcmp("-e", av[i]) == 0)
		{
			if ((i = fc_option_e(av, fc_infos, i, context)) <= 0)
				return (i);
		}
		else
		{
			j = 1;
			while (av[i][j])
			{
				if (ft_strchr("lnrs", av[i][j]))
					add_valid(fc_infos, av[i][j++]);
				else
					return (0);
			}
		}
		av[i] ? i++ : 0;
	}
	return (i);
}

int				fc_get_hist_numrev(t_list *find, t_list *hist)
{
	int num;

	num = 0;
	while (hist && hist != find)
	{
		hist = hist->next;
		num++;
	}
	if (hist != NULL)
		return (num);
	return (0);
}

int				fc_get_hist_num(t_sh_state *sh_state, const char *str)
{
	int i = 0;
	int is_alpha = 0;
	int neg = 0;
	t_list *find = NULL;

	if (str[i] == '-')
		neg++;
	while (str[i + neg] && is_alpha == 0)
		is_alpha += !ft_isdigit(str[i++]);
	dprintf(1, "%i\n", is_alpha);
	if (!is_alpha)
	{
		if (neg == 0)
			return (ft_atoi(str));
		else
		{
			find = get_history_index_rev(sh_state->history, ft_atoi(str + 1));
			return (fc_get_hist_numrev(find, sh_state->history));
		}
	}
	else
	{
		return (0);
	}
}

static int		fc_print(t_sh_state *sh_state, int first, int last, t_builtin_context *context)
{
	(void)sh_state;
	(void)context;

	dprintf(1, "first = %i\n", first);
	dprintf(1, "last  = %i\n", last);
	return (0);
}

static int		fc_dispatch(t_sh_state *sh_state, const char **av, t_fc_infos *fc_infos, t_builtin_context *context)
{
	int i;
	//int first = 0;
	//int last = 0;

	i = 0;
	print_error(context->origin, "test", context->fds.err);
	if (av[0])
	{
		fc_infos->first = fc_get_hist_num(sh_state, av[0]);
		if (av[1])
			fc_infos->last = fc_get_hist_num(sh_state, av[1]);
	}
	if (fc_infos->opts != NULL && ft_strchr(fc_infos->opts, 'l') != NULL)
		return (fc_print(sh_state, fc_infos->first, fc_infos->last, context));
	return (0);
}

int				builtin_fc(t_sh_state *sh_state, int ac, const char **av, t_builtin_context *context)
{
	t_fc_infos	*fc_infos;
	int			args_i;

	(void)ac;
	fc_infos = ft_memalloc(sizeof(t_fc_infos));
	add_origin(&context->origin, "fc");
	fc_infos->editor = NULL;
	if (!(fc_infos->opts = ft_strnew(5)))
		return (-1);
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
