/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_execution.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 19:16:23 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 05:24:40 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_execution.h"

#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-parameter"

int				exec_builtin_as_process(t_sh_state *sh_state, t_cmd *cmd,
t_builtin_func builtin, t_context *context)
{
	pid_t	pid;
	int		res;
	t_proc	*proc;
	const char **arg;
	t_builtin_context	*builtin_context;
	int		new_pipe[3];
	int		err;

	new_pipe[0] = 0;
	builtin_context = context->builtin_context;
	builtin_context->background = context->background;
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
		use_pipes(context, new_pipe);
		if ((err = handle_redir(cmd, context->builtin_context->origin)) != 0)
			exit(err);
		else
		{
			reset_signal_handlers();
			setpgid(0, context->proc_grp->pgid);
			res = builtin(sh_state,
		ft_arraylen((const void **)arg), arg, builtin_context);
			exit(res);
		}
	}
	else
	{
		if ((proc = new_proc(pid, cmd->arg[0], context->last)) == NULL)
			return (1);
		if (register_process(context, proc, new_pipe) == 1)
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
		exit(err);
	context->builtin_context->background = 0;
	err = builtin(sh_state, ft_arraylen((const void **)cmd->arg),
(const char **)cmd->arg, context->builtin_context);
	dup2(std_state[0], 0);
	close(std_state[0]);
	dup2(std_state[1], 1);
	close(std_state[1]);
	dup2(std_state[2], 2);
	close(std_state[2]);
	return (err);
}
