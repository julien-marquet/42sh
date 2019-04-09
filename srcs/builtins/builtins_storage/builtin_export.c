/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_export.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 23:37:38 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 21:11:13 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_storage/builtin_export.h"

static int	handle_export(t_list **internal_storage, int ac, const char **av,
int i)
{
	char	*value;
	char	*name;

	while (i < ac)
	{
		if ((value = ft_strchr(av[i], '=')) == NULL)
			update_exported_flag(*internal_storage, av[i], 1);
		else
		{
			value++;
			if ((name = ft_strndup(av[i],
		ft_strlen(av[i]) - ft_strlen(value) - 1)) == NULL)
				return (1);
			if (add_entry_storage(internal_storage, name, value, 1) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int		builtin_export(t_sh_state *sh_state, int ac, const char **av,
t_builtin_context *context)
{
	int		i;
	char	*opts;

	add_origin(&context->origin, "export");
	if (ac == 1)
	{
		print_env(sh_state->internal_storage, context->fds.out);
		return (0);
	}
	else
	{
		if ((i = handle_builtin_options(av, "p", &opts, context)) == -1)
			return (1);
		else if (i == 0)
		{
			print_error(context->origin, "usage: export [-p] [name[=value] ... ]",
		context->fds.err);
			return (1);
		}
		else
		{
			if (opts != NULL && ft_strchr(opts, 'p') != NULL)
				print_env(sh_state->internal_storage, context->fds.out);
			else
				return (handle_export(&sh_state->internal_storage, ac, av, i));
			return (0);
		}
	}
}
