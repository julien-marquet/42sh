/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_alias.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 00:13:07 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 01:37:08 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_aliases/builtin_alias.h"

static int	print_alias(t_list *aliases, const char *name)
{
	t_list	*node;

	if ((node = find_alias_by_name(aliases, name)) == NULL)
	{
		write(2, "alias: ", 7);
		ft_putstr_fd(name, 2);
		write(2, ": not found\n", 12);
		return (1);
	}
	else
	{
		write(2, node->content, node->content_size);
		write(2, "\n", 1);
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

int		builtin_alias(t_sh_state *sh_state, int ac, const char **av, int fd_out)
{
	int		i;
	int		res;

	res = 0;
	if (ac == 1)
		print_aliases(sh_state->aliases, fd_out);
	i = 1;
	while (i < ac)
	{
		if (ft_strchr(av[i], '=') == NULL)
			res |= print_alias(sh_state->aliases, av[i]);
		else
		{
			if (assign_alias(&sh_state->aliases, av[i]) == 1)
				return (1);
		}
		i++;
	}
	return (res);
}
