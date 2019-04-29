/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_binary.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/20 22:42:46 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 14:53:40 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec_binary.h" 
#include "storage/storage_tmp.h"

int		exec_binary(t_cmd *cmd, char **env, const char *path, t_context *context)
{
	pid_t	pid;
	t_proc	*proc;
	const char **arg;
	int		new_pipe[3];
	int		err;
	char	*origin;
	char	**updated_env;

	origin = NULL;
	add_origin(&origin, NAME);
	new_pipe[0] = 0;
	arg = (const char **)cmd->arg;
	if (cmd->red && ft_strcmp(cmd->red, "|") == 0)
	{
		if (pipe(&new_pipe[1]) == -1)
			return (1);
		new_pipe[0] = 1;
	}
	pid = fork();
	if (pid == 0)
	{
		reset_signal_handlers();
		setpgid(0, context->proc_grp->pgid);
		use_pipes(context, new_pipe);
		if ((err = handle_redir(cmd, origin)) != 0)
			exit(err);
		else
		{
			if (cmd->env == NULL)
				updated_env = env;
			else
				if ((updated_env = update_env(env, cmd->env)) == NULL)
					exit(1);
			if (execve(path, cmd->arg, updated_env) == -1)
				exit(1);
			if (cmd->env != NULL)
				free(updated_env);
		}
	}
	else
	{
		ft_strdel(&origin);
		if ((proc = new_proc(pid, cmd->arg[0], context->last)) == NULL)
			return (1);
		if (register_process(context, proc, new_pipe) == 1)
			return (1);
	}
	return (0);
}

