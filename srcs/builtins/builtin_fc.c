/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_fc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 22:10:25 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/24 17:04:48 by mmoya       ###    #+. /#+    ###.fr     */
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

static void		add_valid(char **opts, char new)
{
	size_t len;
	
	len = ft_strlen(*opts);		
	if (!ft_strchr(*opts, new))
		(*opts)[len] = new;
}

static int		fc_option_e(const char **av, char **editor, int i, t_builtin_context *context)
{
	if (av[++i] != NULL)
	{
		if (*editor != NULL)
			ft_strdel(editor);
		if (!(*editor = ft_strdup(av[i])))
			return (-1);
	}
	else
	{
		print_error(context->origin, "-e: option requires an argument", context->fds.err);
		return (0);
	}
	return (i);
}

static int		fc_options(const char **av, char **opts, char **editor, t_builtin_context *context)
{
	int i;
	int j;

	i = 1;
	while (av[i] && is_builtin_option(av[i]))
	{
		if (ft_strcmp("-e", av[i]) == 0)
		{
			if ((i = fc_option_e(av, editor, i, context)) <= 0)
				return (i);
		}
		else
		{
			j = 1;
			while (av[i][j])
			{
				if (ft_strchr("lnrs", av[i][j]))
					add_valid(opts, av[i][j++]);
				else
					return (0);
			}
		}
		av[i] ? i++ : 0;
	}
	return (i);
}

static int		fc_dispatch(t_sh_state *sh_state, const char **av, char *opts, char *editor, t_builtin_context *context)
{
	int i;
	char *first = NULL;
	char *last = NULL;

	i = 0;
	(void)sh_state;
	(void)editor;
	print_error(context->origin, "test", context->fds.err);
	if (av[0])
	{
		if (!(first = ft_strdup(av[0])))
			return (-1);
		if (av[1])
			if (!(last = ft_strdup(av[1])))
				return (-1);
	}
	dprintf(1, "%s %s\n", first, last);
	if (opts != NULL && ft_strchr(opts, 'l') != NULL)
		;
	return (0);
}

int				builtin_fc(t_sh_state *sh_state, int ac, const char **av, t_builtin_context *context)
{
	int		args_i;
	char	*opts;
	char	*editor;

	(void)ac;
	add_origin(&context->origin, "fc");
	editor = NULL;
	if (!(opts = ft_strnew(5)))
		return (-1);
	if ((args_i = fc_options(av, &opts, &editor, context)) == -1)
		return (1);
	else if (args_i == 0)
	{
		print_error(context->origin, "usage: fc [-e ename] [-nlr] [first] [last] or fc -s [pat=rep] [cmd]", context->fds.err);
		return (1);
	}
	else
		return (fc_dispatch(sh_state, av + args_i, opts, editor, context));
}
