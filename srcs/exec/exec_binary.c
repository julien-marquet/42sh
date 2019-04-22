/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_binary.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/20 22:42:46 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/22 02:46:19 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec_binary.h" 

int		exec_binary(t_cmd *cmd, char **env, const char *path, t_context *context)
{
	pid_t	pid;
	t_proc	*proc;
	const char **arg;
	int		new_pipe[3];

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
		use_pipes(context, new_pipe);
		reset_signal_handlers();
		setpgid(0, context->proc_grp->pgid);
		if (execve(path, cmd->arg, env) == -1)
			exit(1);
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
