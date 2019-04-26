/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_export.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 23:37:38 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/20 03:20:39 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_storage/builtin_export.h"

static void	print_export(t_list *internal_storage, int fd)
{
	t_list	*tmp;
	size_t	len;
	char	*str;
	char	*value;

	tmp = internal_storage;
	while (tmp != NULL)
	{
		if (((t_internal_storage *)(tmp->content))->exported == 1)
		{
			ft_putstr_fd("export ", fd);
			str = ((t_internal_storage *)(tmp->content))->string;
			value = ft_strchr(str, '=') + 1;
			len = ft_strlen(value);
			write(fd, str, ft_strlen(str) - len);
			if (value[0] != '\'')
				write(fd, "\'", 1);
			write(fd, value, len);
			if (value[len - 1] != '\'')
				write(fd, "\'", 1);
			write(fd, "\n", 1);
		}
		tmp = tmp->next;
	}
}

static int	handle_export(t_sh_state *sh_state, const char **av,
int i, t_builtin_context *context)
{
	char	*value;
	char	*name;
	int		res;

	while (av[i] != NULL)
	{
		if ((value = ft_strchr(av[i], '=')) == NULL)
			update_exported_flag(sh_state->internal_storage, &(sh_state->hash_table), av[i], 1);
		else
		{
			value++;
			if ((name = ft_strndup(av[i],
		ft_strlen(av[i]) - ft_strlen(value) - 1)) == NULL)
				return (1);
			if ((res = add_entry_storage(sh_state, name, value, 1)) == -1)
				return (1);
			else if (res == 1)
			{
				print_error(context->origin,
		"Variable name must only contains alphanumerical characters or \'_\'",
		context->fds.err);
			}
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
	int		res;

	add_origin(&context->origin, "export");
	res = 0;
	if (ac == 1)
		print_export(sh_state->internal_storage, context->fds.out);
	else
	{
		if ((i = handle_builtin_options(av, "p", &opts, context)) == -1)
			res = 1;
		else if (i == 0)
		{
			print_error(context->origin,
		"usage: export [-p] [name[=value] ... ]", context->fds.err);
			res = 1;
		}
		else
		{
			if (opts != NULL && ft_strchr(opts, 'p') != NULL)
				print_export(sh_state->internal_storage, context->fds.out);
			else
				res = handle_export(sh_state, av, i, context);
		}
		ft_strdel(&opts);
	}
	return (res);
}
