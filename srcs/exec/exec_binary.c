/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_binary.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/20 22:42:46 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 19:43:44 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec_binary.h"

static void	init_binary_child_data(t_child_data *child_data,
char **env, const char *path)
{
	child_data->new_pipe[0] = 0;
	child_data->path = path;
	child_data->env = env;
}

static int	do_binary_child_work(t_context *context, t_cmd *cmd,
t_child_data child_data)
{
	int		err;
	char	*origin;

	origin = NULL;
	add_origin(&origin, NAME);
	reset_signal_handlers();
	setpgid(0, context->proc_grp->pgid);
	use_pipes(context, child_data.new_pipe);
	if ((err = handle_redir(cmd, origin)) != 0)
	{
		ft_strdel(&origin);
		return (err);
	}
	else
	{
		ft_strdel(&origin);
		if (execve(child_data.path, cmd->arg, child_data.env) == -1)
			return (1);
	}
	return (0);
}

int			exec_binary(t_cmd *cmd, char **env, const char *path,
t_context *context)
{
	pid_t			pid;
	t_proc			*proc;
	t_child_data	child_data;

	init_binary_child_data(&child_data, env, path);
	if (cmd->red && ft_strcmp(cmd->red, "|") == 0)
	{
		if (pipe(&child_data.new_pipe[1]) == -1)
			return (1);
		child_data.new_pipe[0] = 1;
	}
	pid = fork();
	if (pid == 0)
		exit(do_binary_child_work(context, cmd, child_data));
	else
	{
		if ((proc = new_proc(pid, cmd->arg[0], context->last)) == NULL)
			return (1);
		if (register_process(context, proc, child_data.new_pipe) == 1)
			return (1);
	}
	return (0);
}
