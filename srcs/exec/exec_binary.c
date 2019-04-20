/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_binary.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/20 22:42:46 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/20 23:22:30 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec_binary.h" 

int		exec_binary(t_cmd *cmd, char **env, const char *path, t_context *context)
{
	pid_t	pid;
	t_proc	*proc;
	const char **arg;

	arg = (const char **)cmd->arg;
	pid = fork();
	if (pid == 0)
	{
		reset_signal_handlers();
		setpgid(0, context->proc_grp->pgid);
		if (execve(path, cmd->arg, env) == -1)
			exit(1);
		exit(0);
	}
	else
	{
		if ((proc = new_proc(pid, cmd->arg[0], context->last)) == NULL)
			return (1);
		if (register_process(context, proc) == 1)
			return (1);
	}
	return (0);
}
