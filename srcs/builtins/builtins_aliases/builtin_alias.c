/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_alias.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 00:13:07 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 04:03:33 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_aliases/builtin_alias.h"

static int	print_alias(t_list *aliases, const char *name, const t_fds fds)
{
	t_list	*node;

	if ((node = find_alias_by_name(aliases, name)) == NULL)
	{
		write(fds.err, "alias: ", 7);
		ft_putstr_fd(name, fds.err);
		write(fds.err, ": not found\n", 12);
		return (1);
	}
	else
	{
		write(fds.out, node->content, node->content_size);
		write(fds.out, "\n", 1);
		return (0);
	}
}

static int	assign_alias(t_list **aliases, const char *str)
{
	char	*name;
	char	*value;

	if ((value = ft_strchr(str, '=')) == NULL)
		return (1);
	if ((value = ft_strdup(value + 1)) == NULL)
		return (1);
	if ((name = ft_strndup(str,
ft_strlen(str) - ft_strlen(value) - 1)) == NULL)
		return (1);
	if (add_alias(aliases, name, value) == 1)
		return (1);
	free(value);
	free(name);
	return (0);
}

int		builtin_alias(t_sh_state *sh_state, int ac, const char **av,
const t_fds fds)
{
	int		i;
	int		res;
	char	*opts;

	res = 0;
	if (ac == 1)
		print_aliases(sh_state->aliases, fds.out);
	else
	{
		if ((i = handle_builtin_options(av, "p", &opts, fds.err)) <= 0)
			return (1);
		if (opts != NULL && ft_strchr(opts, 'p') != NULL)
			print_aliases(sh_state->aliases, fds.out);
		while (i < ac)
		{
			if (ft_strchr(av[i], '=') == NULL)
				res |= print_alias(sh_state->aliases, av[i], fds);
			else
			{
				if (assign_alias(&sh_state->aliases, av[i]) == 1)
					return (1);
			}
			i++;
		}
		ft_strdel(&opts);
	}
	return (res);
}
