/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 18:24:42 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 02:44:24 by jmarquet    ###    #+. /#+    ###.fr     */
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

t_list	*create_test_cmd_chain(t_input_data *input_data)
{
	char 				**test;
	t_test_cmd			test_cmd;
	int					i = 0;
	t_list				*lst, *node;

	if (input_data->active_buf->len > 0) {
		input_data->active_buf->len -= 1;
		input_data->active_buf->buf[input_data->active_buf->len] = '\0';
	}
	test = NULL;
	test = ft_strsplit(input_data->active_buf->buf, ' ');
	lst = NULL;
	while (test[i] != NULL && test[i + 1] != NULL) {
		if (i % 2 == 0) {
			test_cmd.str = ft_memalloc(sizeof(char *) * 2);
			test_cmd.redir = 0;
			test_cmd.str[0] = ft_strdup(test[i]);
			test_cmd.str[1] = NULL;
			test_cmd.background = 0;
			node = ft_lstnew(&test_cmd, sizeof(test_cmd));
			ft_lstappend(&lst, node);
		} else {
			((t_test_cmd *)node->content)->redir = ft_atoi(test[i]);
		}
		i++;
	}
	if (i >= 2)
		((t_test_cmd *)node->content)->background = ft_atoi(test[i]);
	return (lst);
}

int		main(int ac, char **av, char **env)
{
	t_sh_state		*sh_state;
	t_input_data	*input_data;
	t_list			*cmd_list;
	char			*job_name;

	ac = av[0][0];
	setsid();
	if ((sh_state = init_sh()) == NULL)
		return (1);
	if ((input_data = init_input_data()) == NULL)
		return (1);
	if ((sh_state->internal_storage = init_env((const char **)env)) == NULL)
		return (1);

	signal(SIGWINCH, handle_sigwinch);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, handle_sigchld);

	sh_state->shell_pid = getpgid(0);
	tcsetpgrp(0, sh_state->shell_pid);
	while (sh_state->exit_sig == 0)
	{

		display_jobs_alert();
		flush_exited();
		if (handle_input(sh_state, input_data, NULL) == 1)
		{
			sh_state->status = 1;
			break ;
		}
		dprintf(2, "OUTPUT = %s", input_data->active_buf->buf);
		cmd_list = create_test_cmd_chain(input_data);
		job_name = ft_strdup(input_data->active_buf->buf);
		exec_cmd_list(sh_state, cmd_list, job_name);
		reset_dyn_buf(input_data->active_buf);
	}
	exit_sh(sh_state, input_data);
	return (0);
}

// handle escape \ for aliases
// piste =>
// The waitpid() function allows the calling thread to obtain status information for one of its child processes. The calling thread suspends processing until status information is available for the specified child process, if the options argument is 0. A suspended waitpid() function call can be interrupted by the delivery of a signal whose action is either to run a signal-catching function or to terminate the process. When waitpid() is successful, status information about how the child process ended (for example, whether the process ended normally) is stored in the location specified by stat_loc.