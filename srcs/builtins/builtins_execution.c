/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_execution.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 19:16:23 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 15:44:18 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "storage/storage_tmp.h"
#include "builtins/builtins_execution.h"

static int		do_child_work(t_sh_state *sh_state,
t_context *context, t_child_data *child_data, t_cmd *cmd)
{
	int		err;
	int		res;

	reset_signal_handlers();
	setpgid(0, context->proc_grp->pgid);
	use_pipes(context, child_data->new_pipe);
	if ((err = handle_redir(cmd, context->builtin_context->origin)) != 0)
		return (err);
	else
	{
		if (update_builtin_env(&(sh_state->internal_storage), cmd->env) == -1)
			return (1);
		res = child_data->builtin(sh_state,
		ft_arraylen((const void **)cmd->arg), (const char **)cmd->arg,
	context->builtin_context);
		ft_lstdel(&((sh_state)->internal_storage),
	free_lstinternal_storage_node);
		return (res);
	}
	return (0);
}

static void		init_child_data(t_child_data *child_data,
t_builtin_func builtin)
{
	child_data->new_pipe[0] = 0;
	child_data->builtin = builtin;
}

int				exec_builtin_as_process(t_sh_state *sh_state, t_cmd *cmd,
t_builtin_func builtin, t_context *context)
{
	pid_t				pid;
	t_proc				*proc;
	t_builtin_context	*builtin_context;
	t_child_data		child_data;

	init_child_data(&child_data, builtin);
	builtin_context = context->builtin_context;
	builtin_context->is_process = 1;
	if (cmd->red && ft_strcmp(cmd->red, "|") == 0)
	{
		if (pipe(&child_data.new_pipe[1]) == -1)
			return (1);
		child_data.new_pipe[0] = 1;
	}
	pid = fork();
	if (pid == 0)
		exit(do_child_work(sh_state, context, &child_data, cmd));
	else
	{
		if ((proc = new_proc(pid, cmd->arg[0], context->last)) == NULL)
			return (1);
		if (register_process(context, proc, child_data.new_pipe) == 1)
			return (1);
	}
	return (0);
}

int				exec_builtin_as_function(t_sh_state *sh_state, t_cmd *cmd,
t_builtin_func builtin, t_context *context)
{
	int		err;
	int		std_state[3];

	std_state[0] = dup(0);
	std_state[1] = dup(1);
	std_state[2] = dup(2);
	if ((err = handle_redir(cmd, context->builtin_context->origin)) != 0)
		return (err);
	context->builtin_context->is_process = 0;
	if (update_builtin_env(&(sh_state->internal_storage), cmd->env) == -1)
		return (1);
	err = builtin(sh_state, ft_arraylen((const void **)cmd->arg),
(const char **)cmd->arg, context->builtin_context);
	remove_tmp_env(&(sh_state->internal_storage));
	dup2(std_state[0], 0);
	close(std_state[0]);
	dup2(std_state[1], 1);
	close(std_state[1]);
	dup2(std_state[2], 2);
	close(std_state[2]);
	return (err);
}
