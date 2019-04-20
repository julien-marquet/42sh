/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_dispatcher.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 23:32:49 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/20 23:24:41 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec_dispatcher.h"

int		exec_dispatcher(t_sh_state *sh_state, t_cmd *cmd,
t_context *context)
{
	int				res;
	size_t			err;
	char			*path;
	char			**env;

	res = 0;
	dprintf(2, "searchinf for exe\n");
	if ((path = get_bin_path(cmd->arg, &sh_state->hash_table, sh_state->internal_storage, &err)) == NULL)
	{
		// err
		if (err == 1)
			res = -1;
		// not found
	}
	else
	{
		env = generate_env(sh_state->internal_storage);
		if (exec_binary(cmd, env, path, context) == 1)
			res = -1;
		else
			res = 1;
		// free env
	}
	dprintf(2, "path = %s, res = %d\n", path, res);
	return (res);
}
