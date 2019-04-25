/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_fc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 22:10:25 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 23:52:54 by mmoya       ###    #+. /#+    ###.fr     */
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
	int		i = 0;
	int		is_alpha = 0;
	int		neg = 0;
	t_list	*find = NULL;

	if (str[i] == '-')
		neg++;
	while (str[neg + i] && is_alpha == 0)
		is_alpha += !ft_isdigit(str[neg + i++]);
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
		find = get_history_search(sh_state->history, (char *)str);
		return (fc_get_hist_numrev(find, sh_state->history));
	}
}

size_t			get_hist_len(t_list *hist)
{
	size_t len;

	len = 0;
	while (hist)
	{
		len++;
		hist = hist->next;
	}
	return (len);
}

void			hist_print(t_list *hist, size_t len, int num)
{
	while (hist && num > 0)
	{
		num--;
		dprintf(1, "%zu\t%s\n", len--, hist->content);
		hist = hist->next;
	}
}

void			hist_print_rev(t_list *hist, size_t len, int num)
{
	if (hist && num > 0)
	{
		hist_print_rev(hist->next, len - 1, num - 1);
		dprintf(1, "%zu\t%s\n", len, hist->content);
	}
}

static int		fc_print(t_sh_state *sh_state, t_fc_infos *fc_infos, t_builtin_context *context)
{
	t_list	*tmp;

	tmp = sh_state->history;
	(void)context;
	if (tmp == NULL || tmp->next == NULL)
		return (1);
	tmp = tmp->next;
	if (fc_infos->first == -1)
	{
		if (ft_strchr(fc_infos->opts, 'r'))
			hist_print(tmp, get_hist_len(tmp), 16);
		else
			hist_print_rev(tmp, get_hist_len(tmp), 16);
	}
	else
	{
		/*if (fc_infos->first == -1)
		{
			if (ft_strchr(fc_infos->opts, 'r'))
				hist_print(tmp, get_hist_len(tmp), get_hist_len(sh_state->history) - fc_infos->first);
			else
				hist_print_rev(tmp, get_hist_len(tmp), get_hist_len(sh_state->history) - fc_infos->first);
		}
		else
		{*/
		size_t big = fc_infos->first > fc_infos->last ? fc_infos->first : fc_infos->last;
		size_t small = fc_infos->first > fc_infos->last ? fc_infos->last : fc_infos->first;
		//if (fc_infos->first > fc_infos->last || ft_strchr(fc_infos->opts, 'r'))
		//{
			tmp = get_history_index_rev(sh_state->history, big);
			hist_print(tmp, get_hist_len(tmp), get_hist_len(tmp) - small);
		//}
		//else
		//	tmp = get_history_index_rev(sh_state->history, small);
		
		//}
	}
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
	if (fc_infos->opts != NULL && ft_strchr(fc_infos->opts, 'l') != NULL)
		return (fc_print(sh_state, fc_infos, context));
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
