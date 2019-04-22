/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_unalias.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 00:13:30 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/20 03:09:05 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_aliases/builtin_unalias.h"

static int	handle_remove(t_list **aliases, const char **av,
t_builtin_context *context, int i)
{
	int		res;

	res = 0;
	while (av[i] != NULL)
	{
		if (remove_alias(aliases, av[i]) == 0)
		{
			add_origin(&context->origin, av[i]);
			print_error(context->origin, "not found", context->fds.err);
			res = 1;
		}
		i++;
	}
	return (res);
}

int			builtin_unalias(t_sh_state *sh_state, int ac, const char **av,
t_builtin_context *context)
{
	char	*opts;
	int		i;

	add_origin(&context->origin, "unalias");
	if (ac <= 1)
	{
		print_error(context->origin, "usage: unalias [-a] name [name ...]",
	context->fds.err);
		return (1);
	}
	else
	{
		if ((i = handle_builtin_options(av, "a", &opts, context)) == -1)
			return (1);
		else if (i == 0)
		{
			print_error(context->origin, "usage: unalias [-a] name [name ...]",
		context->fds.err);
		ft_strdel(&opts);
			return (1);
		}
		else if (opts != NULL && ft_strchr(opts, 'a') != NULL)
		{
			remove_all_aliases(&sh_state->aliases);
			ft_strdel(&opts);
			return (0);
		}
		else
		{
			ft_strdel(&opts);
			return (handle_remove(&sh_state->aliases, av, context, i));
		}
	}
}
