/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_unalias.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 00:13:30 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 18:01:06 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_aliases/builtin_unalias.h"

static int	handle_options(t_list **aliases, const char *opt, t_builtin_context *context)
{
	if (ft_strcmp(opt, "-a") != 0)
	{
		write(context->fds.err, "unalias: usage: unalias [-a] name [name ...]\n", 45);
		return (1);
	}
	else
	{
		remove_all_aliases(aliases);
		return (0);
	}
}

static int	handle_remove(t_list **aliases, int ac, const char **av,
t_builtin_context *context)
{
	int		i;
	int		res;

	i = 1;
	res = 0;
	while (i < ac)
	{
		if (remove_alias(aliases, av[i]) == 0)
		{
			write(context->fds.err, "unalias: ", 9);
			ft_putstr_fd(av[i], context->fds.err);
			write(context->fds.err, ": not found\n", 12);
			res = 1;
		}
		i++;
	}
	return (res);
}

int			builtin_unalias(t_sh_state *sh_state, int ac, const char **av,
t_builtin_context *context)
{
	if (ac <= 1)
	{
		write(context->fds.err, "unalias: usage: unalias [-a] name [name ...]\n", 45);
		return (1);
	}
	else
	{
		if (av[1][0] == '-' && av[1][1] != '\0')
			return (handle_options(&sh_state->aliases, av[1], context));
		else
			return (handle_remove(&sh_state->aliases, ac, av, context));
	}
}
