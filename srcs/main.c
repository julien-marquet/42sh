/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 18:24:42 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/12 20:41:46 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "common.h"
#include "sh.h"
#include "editing/input/input.h"
#include "data/input_data.h"
#include "signal_handler.h"
#include "storage/storage.h"
#include "builtins/builtins.h"
#include "storage/storage.h"
#include "aliases/aliases.h"
#include "exec/exec.h"

int		main(int ac, char **av, char **env)
{
	t_sh_state		*sh_state;
	t_input_data	*input_data;
	int				i;

	i = 0;
	ac = av[0][0];
	setsid();
	if ((sh_state = init_sh()) == NULL)
		return (1);
	if ((input_data = init_input_data()) == NULL)
		return (1);
	if ((sh_state->internal_storage = init_env((const char **)env)) == NULL)
		return (1);
	signal(SIGWINCH, handle_sigwinch);
	signal (SIGINT, SIG_IGN);
	signal (SIGQUIT, SIG_IGN);
	signal (SIGTSTP, SIG_IGN);
	signal (SIGTTIN, SIG_IGN);
	signal (SIGTTOU, SIG_IGN);
	signal (SIGCHLD, SIG_IGN);
	sh_state->shell_pid = getpgid(0);
	tcsetpgrp(0, sh_state->shell_pid);
	dprintf(2, "sid= %d, pgid = %d\n", getsid(0), sh_state->shell_pid);
	while (sh_state->exit_sig == 0)
	{
		display_jobs_alert();
		dprintf(1, "alors\n");
		if (handle_input(sh_state, input_data, NULL) == 1)
		{
			dprintf(2, "failure");
			sh_state->status = 1;
			break ;
		}
		dprintf(2, "OUTPUT = %s", input_data->active_buf->buf);

		char 	**test;
		t_builtin_context	*context = ft_memalloc(sizeof(t_builtin_context));

		context->fds.err = 2;
		context->fds.in = 0;
		context->fds.out = 1;
		add_origin(&context->origin, "42sh");
		if (input_data->active_buf->len > 0)
		{
			input_data->active_buf->len -= 1;
			input_data->active_buf->buf[input_data->active_buf->len] = '\0';
		}
		test = NULL;
		test = ft_strsplit(input_data->active_buf->buf, ' ');
		execute(sh_state, test);
		reset_dyn_buf(input_data->active_buf);
	}
	exit_sh(sh_state, input_data);
	return (0);
}

// handle escape \ for aliases
// piste =>
// The waitpid() function allows the calling thread to obtain status information for one of its child processes. The calling thread suspends processing until status information is available for the specified child process, if the options argument is 0. A suspended waitpid() function call can be interrupted by the delivery of a signal whose action is either to run a signal-catching function or to terminate the process. When waitpid() is successful, status information about how the child process ended (for example, whether the process ended normally) is stored in the location specified by stat_loc.