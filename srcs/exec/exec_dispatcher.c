/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_dispatcher.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 23:32:49 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 23:09:26 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec_dispatcher.h"

static int	get_path_exec(char **path, t_cmd *cmd, t_sh_state *sh_state)
{
	int		res;
	int		err;

	res = 0;
	err = 0;
	if (cmd->arg && is_absolute_path(cmd->arg[0]))
	{
		if ((res = test_bin((const char *)cmd->arg[0])) == 0)
			*path = ft_strdup(cmd->arg[0]);
		else if (res != -1)
			res--;
	}
	else if ((*path = ft_strdup(get_bin_path(
(const char **)cmd->arg, &sh_state->hash_table,
sh_state->internal_storage, &err))) == NULL)
		res = err;
	return (res);
}

/*
**	return -1 critical, 0 = success, 1 = notfound,
**	2 wrong permission, 3 not a regfile
*/

int			handle_null_path(t_cmd *cmd, int err)
{
	char			*origin;

	origin = NULL;
	add_origin(&origin, NAME);
	handle_path_error(origin, cmd->arg[0], err);
	ft_strdel(&origin);
	return (0 - err);
}

int			exec_dispatcher(t_sh_state *sh_state, t_cmd *cmd,
t_context *context)
{
	int				res;
	char			*path;
	char			**env;

	path = NULL;
	res = get_path_exec(&path, cmd, sh_state);
	if (path != NULL)
	{
		if (update_builtin_env(&(sh_state->internal_storage), cmd->env) == -1)
			return (1);
		env = generate_env(sh_state->internal_storage);
		remove_tmp_env(&(sh_state->internal_storage));
		if (exec_binary(cmd, env, path, context) == 1)
			res = -1;
		else
			res = 1;
		free_arr(env);
		ft_strdel(&path);
	}
	else
		res = handle_null_path(cmd, res);
	return (res);
}
