/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_execution.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 19:16:23 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 02:20:50 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_execution.h"

int				background_exec_builtin(t_sh_state *sh_state, const char **av,
t_builtin_func builtin, t_builtin_context *context)
{
	pid_t	pid;
	int		stat_loc;
	int		res;

	pid = fork();
	if (pid == 0)
	{
		set_term_state_backup(sh_state);
		res = builtin(sh_state, ft_arraylen((const void **)av), av, context);
		set_term_state(sh_state);
		exit(res);
	}
	else
	{
		waitpid(pid, &stat_loc, WUNTRACED);
		return (WEXITSTATUS(stat_loc));
	}
}

int				exec_builtin(t_sh_state *sh_state, const char **av,
t_builtin_func builtin, t_builtin_context *context)
{
	return (builtin(sh_state, ft_arraylen((const void **)av), av, context));
}
