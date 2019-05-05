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

int			check_file_exec(const char *path)
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

static int	remove_origin(char **origin, const char *name)
{
	size_t	len;
	char	*new;

	len = ft_strlen(*origin) - ft_strlen(name) - 2;
	if ((new = malloc(len + 1)) == NULL)
		return (-1);
	ft_strncpy(new, *origin, len);
	new[len] = '\0';
	free(*origin);
	*origin = new;
	return (0);
}

int			print_type(char **origin, const char *name, char **value,
t_cmd_type type)
{
	char	*str;

	if (type == cmd_notfound)
	{
		add_origin(origin, name);
		print_error(*origin, "not found", 2);
		if (remove_origin(origin, name) == -1)
			return (1);
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

int			assign_cmd_type(t_sh_state *sh_state, const char *name,
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

static int	loop_args(t_builtin_context *context, t_sh_state *state,
			int ac, const char **av)
{
	int			i;
	t_cmd_type	type;
	char		*value;

	i = 1;
	while (i < ac)
	{
		type = cmd_notfound;
		if ((value = get_alias(state->aliases, av[i])) != NULL)
			type = cmd_alias;
		else
		{
			if (assign_cmd_type(state, av[i], &value, &type) == 1)
				return (1);
		}
		print_type(&context->origin, av[i], &value, type);
		i += 1;
	}
	return (0);
}

int			builtin_type(t_sh_state *sh_state, int ac,
const char **av, t_builtin_context *context)
{
	add_origin(&context->origin, "type");
	if (ac < 2)
	{
		print_error(context->origin, "usage: type name...", 2);
		return (1);
	}
	else
		return (loop_args(context, sh_state, ac, av));
	return (0);
}
