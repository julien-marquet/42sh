/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 18:24:42 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 00:12:36 by jmarquet    ###    #+. /#+    ###.fr     */
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
	if ((sh_state = init_sh()) == NULL)
		return (1);
	if ((input_data = init_input_data()) == NULL)
		return (1);
	if ((sh_state->internal_storage = init_env((const char **)env)) == NULL)
		return (1);
	while (i < 32)
		signal(i++, handle_all);
	while (sh_state->exit_sig == 0)
	{
		if (handle_input(sh_state, input_data, NULL) == 1)
		{
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
		execute(sh_state, (const char **)test);
		reset_dyn_buf(input_data->active_buf);
	}
	exit_sh(sh_state, input_data);
	return (0);
}

// handle escape \ for aliases