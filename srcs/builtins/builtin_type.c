/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_type.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/25 05:04:09 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 06:29:33 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_type.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

int		check_file_exec(const char *path)
{
	struct stat	f_stat;

	if (path == NULL)
		return (-1);
	if (access(path, F_OK) == -1)
		return (1);
	if (access(path, X_OK) == -1)
		return (2);
	if (stat(path, &f_stat) == -1)
		return (-1);
	if (S_ISREG(f_stat.st_mode) == 0)
		return (3);
	return (0);
}

int		print_type(char **origin, const char *name, char **value,
t_cmd_type type)
{
	char	*str;

	add_origin(origin, name);
	if (type == cmd_notfound)
	{
		print_error(*origin, "not found", 2);
		return (1);
	}
	if (type == cmd_alias)
		str = ft_construct_str(4, name, " is aliased to '", *value, "'");
	else if (type == cmd_builtin)
		str = ft_construct_str(2, name, " is a shell builtin");
	if (type == cmd_executable)
		str = ft_construct_str(3, name, " is ", *value);
	if (str != NULL)
	{
		ft_putendl_fd(str, 1);
		ft_strdel(&str);
	}
	ft_strdel(value);
	return (0);
}

int		assign_cmd_type(t_sh_state *sh_state, const char *name,
char **value, t_cmd_type *type)
{
	int			err;

	if ((*value = get_alias(sh_state->aliases, name)) != NULL)
		*type = cmd_alias;
	else
	{
		if (ft_strchr(name, '/') != NULL)
		{
			if (check_file_exec(name) == 0)
			{
				*type = cmd_executable;
				if ((*value = ft_strdup(name)) == NULL)
					return (1);
			}
		}
		else
		{
			if (builtin_exist(name) == 1)
				*type = cmd_builtin;
			else if ((*value = ft_strdup(get_bin_path(&name,
		&sh_state->hash_table, sh_state->internal_storage, &err))) != NULL)
				*type = cmd_executable;
		}
	}
	return (0);
}

int		builtin_type(t_sh_state *sh_state, int ac,
const char **av, t_builtin_context *context)
{
	t_cmd_type	type;
	char		*value;

	type = cmd_notfound;
	value = NULL;
	add_origin(&context->origin, "type");
	if (ac < 2)
	{
		print_error(context->origin, "usage: type name...", 2);
		return (1);
	}
	else
	{
		if ((value = get_alias(sh_state->aliases, av[1])) != NULL)
			type = cmd_alias;
		else
		{
			if (assign_cmd_type(sh_state, av[1], &value, &type) == 1)
				return (1);
		}
	}
	return (print_type(&context->origin, av[1], &value, type));
}
