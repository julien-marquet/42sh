/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_execution.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 19:16:23 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 20:54:20 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_execution.h"

int				background_exec_builtin(t_sh_state *sh_state, const char **av,
t_builtin_func builtin, int fd_out)
{
	pid_t	pid;
	int		stat_loc;
	int		res;

	pid = fork();
	if (pid == 0)
	{
		set_term_state_backup(sh_state);
		res = builtin(sh_state, ft_arraylen((const void **)av), av, fd_out);
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
t_builtin_func builtin, int fd_out)
{
	return (builtin(sh_state, ft_arraylen((const void **)av), av, fd_out));
}
