/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_alias.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 00:13:07 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 15:18:04 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_aliases/builtin_alias.h"

static int	print_alias(t_list *aliases, const char *name,
t_builtin_context *context)
{
	t_list	*node;
	size_t	len;
	char	*value;
	char	*origin;

	if ((node = find_alias_by_name(aliases, name)) == NULL)
	{
		if ((origin = ft_strdup(context->origin)) == NULL)
			return (1);
		add_origin(&origin, name);
		print_error(origin, "not found", 2);
		free(origin);
		return (1);
	}
	else
	{
		ft_putstr_fd("alias ", 1);
		value = ft_strchr((char *)(node->content), '=') + 1;
		len = ft_strlen(value);
		write(1, (char *)(node->content),
	ft_strlen((char *)(node->content)) - len);
		if (value[0] != '\'')
			write(1, "\'", 1);
		write(1, value, len);
		if (value[len - 1] != '\'')
			write(1, "\'", 1);
		write(1, "\n", 1);
		return (0);
	}
}

static int	assign_alias(t_list **aliases, const char *str, char **origin)
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
	if (add_alias(aliases, name, value) == 0)
	{
		add_origin(origin, name);
		print_error(*origin, "invalid alias name", 2);
		free(value);
		free(name);
		return (1);
	}
	free(value);
	free(name);
	return (0);
}

int		builtin_alias(t_sh_state *sh_state, int ac, const char **av,
t_builtin_context *context)
{
	int		i;
	int		res;
	char	*opts;

	res = 0;
	add_origin(&context->origin, "alias");
	if (ac == 1)
		print_aliases(sh_state->aliases, 1);
	else
	{
		if ((i = handle_builtin_options(av, "p", &opts, context)) == -1)
			res = 1;
		else if (i == 0)
		{
			print_error(context->origin,
		"usage: alias [-p] [name[=value] ... ]", 2);
			res = 1;
		}
		else
		{
			if (opts != NULL && ft_strchr(opts, 'p') != NULL)
				print_aliases(sh_state->aliases, 1);
			while (i < ac)
			{
				if (ft_strchr(av[i], '=') == av[i] ||
			ft_strchr(av[i], '=') == NULL)
					res |= print_alias(sh_state->aliases, av[i], context);
				else
				{
					if (assign_alias(&sh_state->aliases, av[i],
				&context->origin) == 1)
						res = 1;
				}
				i++;
			}
			ft_strdel(&opts);
		}
	}
	return (res);
}
