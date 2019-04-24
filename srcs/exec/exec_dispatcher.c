/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_dispatcher.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 23:32:49 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 01:42:56 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec_dispatcher.h"

static int	is_absolute_path(const char *path)
{
	return (ft_strchr(path, '/') != NULL);
}

/*
**	return -1 critical, 0 = success, 1 = notfound,
**	2 wrong permission, 3 not a regfile
*/

int		exec_dispatcher(t_sh_state *sh_state, t_cmd *cmd,
t_context *context)
{
	int				res;
	size_t			err;
	char			*path;
	char			**env;
	char			*origin;

	err = 0;
	res = 0;
	path = NULL;
	origin = NULL;
	add_origin(&origin, NAME);
	if (cmd->arg && is_absolute_path(cmd->arg[0]))
	{
		if ((res = test_bin(cmd->arg[0])) != 0)
			handle_path_error(origin, cmd->arg[0], res);
		else
			path = ft_strdup(cmd->arg[0]);
	}
	else if ((path = get_bin_path(cmd->arg, &sh_state->hash_table,
sh_state->internal_storage, &err)) == NULL)
	{
		if (err == 1)
			res = -1;
		if (err == 0)
			res = 1;
	}
	if (path != NULL)
	{
		env = generate_env(sh_state->internal_storage);
		if (exec_binary(cmd, env, path, context) == 1)
			res = -1;
		else
			res = 1;
	}
	dprintf(2, "path = %s, res = %d\n", path, res);
	return (res);
}
