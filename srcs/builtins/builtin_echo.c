/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_echo.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 22:59:24 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 23:11:38 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_echo.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

static void	printer(int i, int fd, const char **av, const char *opts)
{
	int		first;

	first = 1;
	while (av[i] != NULL)
	{
		if (first)
			first = 0;
		else
			write(fd, " ", 1);
		ft_putstr_fd(av[i], fd);
		i++;
	}
	if (!opts || ft_strchr(opts, 'n') == NULL)
		write(fd, "\n", 1);
}

int			builtin_echo(t_sh_state *sh_state, int ac,
const char **av, t_builtin_context *context)
{
	int		i;
	char	*opts;

	add_origin(&context->origin, "alias");
	if ((i = handle_builtin_options(av, "n", &opts, context)) == -1)
		return (1);
	else if (i == 0)
	{
		print_error(context->origin, "usage: echo [-n] [args ... ]",
	context->fds.err);
		return (1);
	}
	else
		printer(i, context->fds.out, av, opts);
	ft_strdel(&opts);
	return (0);
}
