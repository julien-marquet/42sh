/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 18:24:42 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 16:25:09 by mmoya       ###    #+. /#+    ###.fr     */
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
#include "parse/parse.h"
#include "storage/storage.h"
#include "builtins/builtins.h"

int		main(int ac, char **av, char **env)
{
	t_sh_state		*sh_state;
	t_input_data	*input_data;
	int				i;
	//char **test;

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
	// add_entry_storage(&sh_state->internal_storage, "OUI", "NON", 0);
	while (sh_state->exit_sig == 0)
	{
		if (handle_input(sh_state, input_data, NULL) == 1)
		{
			sh_state->status = 1;
			break ;
		}
		/*if (input_data->active_buf->len > 0)
		{
			input_data->active_buf->len -= 1;
			input_data->active_buf->buf[input_data->active_buf->len] = '\0';
		}
		test = NULL;
		test = ft_strsplit(input_data->active_buf->buf, ' ');
		builtins_dispatcher(sh_state, (const char **)test, 1, 0);*/
		parse(input_data->active_buf->buf, NULL, sh_state, input_data);
		reset_dyn_buf(input_data->active_buf);
	}
	exit_sh(sh_state, input_data);
	return (0);
}

