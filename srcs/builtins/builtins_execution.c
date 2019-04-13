/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_execution.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 19:16:23 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 02:02:15 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_execution.h"

int				register_process(t_context *context, int pid,
const char *name, const char *grp_name)
{
	t_proc	*proc;
	int		grp_register;

	if ((proc = new_proc(pid, 0, name)) == NULL)
		return (1);
	if ((grp_register = (context->proc_grp == NULL)))
	{
		if ((context->proc_grp = new_proc_grp(pid, grp_name)) == NULL)
			return (1);
	}
	setpgid(pid, context->proc_grp->pgid);
	add_proc(proc, context->proc_grp);
	if (grp_register)
		add_proc_grp(context->proc_grp);

	return (0);
}

void	handle_for(int signo)
{
	dprintf(2, "%d\n", signo);
}

int				background_exec_builtin(t_sh_state *sh_state, const char **av,
t_builtin_func builtin, t_context *context)
{
	pid_t	pid;
	int		res;

	pid = fork();
	if (pid == 0)
	{
		int i = 1;
		while (i < 32)
			signal(i++, SIG_DFL);
		setpgid(0, context->proc_grp != NULL ? context->proc_grp->pgid : 0);
		res = builtin(sh_state,
	ft_arraylen((const void **)av), av, context->builtin_context);
		exit(res);
	}
	else
	{
		return (register_process(context, pid, av[0], av[0]));
	}
}

int				exec_builtin(t_sh_state *sh_state, const char **av,
t_builtin_func builtin, t_context *context)
{
	int		res;
	// init fds based on cmd
	res = builtin(sh_state, ft_arraylen((const void **)av), av, context->builtin_context);
	return (res);
}